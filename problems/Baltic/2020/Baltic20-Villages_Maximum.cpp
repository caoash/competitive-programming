/*
 * Same as DMON BobEnglish except with the construction.
 *
 * Use sets to store the sizes and vectors to actually get the values.
 */

#include <bits/stdc++.h> 
using namespace std;

using ll = long long;

using vi = vector<int>;
using vl = vector<ll>;
#define pb push_back
#define rsz resize
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using pi = pair<int,int>;
#define f first
#define s second
#define mp make_pair

const int MX = 200005;
const int MOD = (int) (1e9 + 7);
const ll INF = (ll) 1e18;

int n;
int dep[MX];
int sz[MX];
vi adj[MX];

void dfs_init(int v, int p) {
    sz[v] = 1;
    for (int to : adj[v]) {
        if (to != p) {
            dfs_init(to, v);
            sz[v] += sz[to];
        } 
    }
}

int find(int v, int p) { 
    for (int to : adj[v]) {
        if (to != p) {
            if (sz[to] > n / 2) {
                return find(to, v);
            }
        }
    }
    return v;
}

set<pi> vals;

void dfs_dep(int v, int p) {
    for (int to : adj[v]) {
        if (to != p) {
            dep[to] = dep[v] + 1;
            dfs_dep(to, v);
        }
    }
}

vi order;

void dfs_get(int v, int p) { 
    for (int to : adj[v]) {
        if (to != p) {
            dfs_get(to, v);
        }
    }
    order.pb(v);
}

int ret[MX];
vi subt[MX];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        u--, v--;
        adj[u].pb(v), adj[v].pb(u);
    }
    dfs_init(0, -1);
    int cent = find(0, -1);
    ll ans = 0;
    dfs_dep(cent, -1);
    for (int i = 0; i < n; i++) ans += dep[i];
    ans *= 2;
    cout << ans << '\n';
    memset(ret, -1, sizeof(ret));
    int cnt = 0;
    for (int to : adj[cent]) {
        order.clear();
        dfs_get(to, cent);
        vals.insert(mp(sz(order), cnt));
        for (auto x : order) {
            subt[cnt].pb(x);
        }
        ++cnt;
    }
    pi guys = mp(-1, -1);;
    while (sz(vals) >= 2) {
        auto fr = (prev(vals.end()));
        auto sec = (prev(prev(vals.end())));
        vals.erase(fr);
        vals.erase(sec);
        int v1 = subt[fr->s].back();
        int v2 = subt[sec->s].back();
        ret[v1] = v2;
        ret[v2] = v1;
        guys = mp(v1, v2);
        subt[fr->s].pop_back();
        subt[sec->s].pop_back();
        pi nxt_fr = mp((fr->f) - 1, fr->s);
        pi nxt_sec = mp((sec->f) - 1, sec->s);
        if (nxt_fr.f != 0) vals.insert(nxt_fr);
        if (nxt_sec.f != 0) vals.insert(nxt_sec);
    }
    if (!vals.empty()) {
        pi fin = *(--vals.end());
        int nod = subt[fin.s].back();
        ret[cent] = nod; 
        ret[nod] = cent;
    } else {
        assert(guys.f != -1);
        assert(n % 2 == 1);
        ret[guys.f] = cent; 
        ret[cent] = guys.s;
        ret[guys.s] = guys.f;
    }
    for (int i = 0; i < n; i++) {
        cout << ret[i] + 1 << " ";
    }
    cout << '\n';
}

