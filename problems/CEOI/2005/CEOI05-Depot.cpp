/*
 * If we create the bipartite "edge graph" with edges representing switching colors and moving objects.
 *
 * Then you can observe this graph has an euler circuit, and the euler circuit creates a valid solution.
 */

#include <bits/stdc++.h> 
using namespace std;

using ll = long long;

using vi = vector<int>;
using vl = vector<ll>;
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define lb lower_bound
#define ub upper_bound

using pi = pair<int,int>;
#define f first
#define s second
#define mp make_pair

const int MX = 405;
const int MOD = (int) (1e9 + 7);
const ll INF = (ll) 1e18;

int n, m; 
multiset<int> adj[2 * MX];
int has[MX][MX];
vi cyc;
vi locs[MX][MX];

int red(int a, int b) {
    return n * b + a;
}

pi rev(int x) {
    return mp((x >= n ? x - n : x), x >= n ? 1 : 0);
}

void dfs(int v) {
    if (adj[v].empty()) return;
    while (sz(adj[v])) {
        int to = *(adj[v].begin());
        adj[v].erase(adj[v].begin());
        dfs(to);
        cyc.pb(v);
    }
}

int main(){
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    vi a(n * m);
    vi b(n * m + 1, -1);
    for (int i = 0; i < n * m; i++) {
        cin >> a[i];
        a[i]--;
        b[i] = a[i];
        has[i / m][a[i]]++;
        locs[i / m][a[i]].pb(i);
    }
    for (int i = 0; i < n; i++) 
    for (int j = 0; j < m; j++) {
        if (!has[i][j]) {
            adj[red(j, 1)].insert(red(i, 0));
        } else {
            for (int k = 0; k < has[i][j] - 1; k++) {
                adj[red(i, 0)].insert(red(j, 1));
            }
        }
    }
    vector<pi> ret;
    int ccs = 0;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        dfs(i); 
        if (sz(cyc) > 1) {
            reverse(all(cyc));
            ++ccs;
            ans += (sz(cyc) / 2);
            int nxt = n * m;
            for (int j = sz(cyc) - 1; j >= 0; j -= 2) {
                int val = rev(cyc[j]).f;     
                int pos = rev(cyc[j - 1]).f;
                int loc = locs[pos][val].back();
                locs[pos][val].pop_back();
                ret.pb(mp(loc, nxt));
                nxt = loc;
            }
            ret.pb(mp(n * m, nxt));
        }
        cyc.clear();
    }
    ans += ccs;
    cout << ans << '\n';
    for (auto x : ret) {
        cout << x.f + 1 << " " << x.s + 1 << '\n';
    }
}

