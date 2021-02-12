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

const int MX = 200005;
const int MOD = (int) (1e9 + 7);
const ll INF = (ll) 1e18;

int n;
vi adj[MX];
int siz[MX];
int anc[MX];

void dfs_init(int v, int p) {
    siz[v] = 1;
    for (int to : adj[v]) {
        if (to != p) {
            dfs_init(to, v);
            siz[v] += siz[to];
            anc[to] = v;
        }
    }
}

int gud(int v) {
    int big = -1;
    for (int to : adj[v]) {
        if (to != anc[v]) big = max(big, siz[to]);
    }
    big = max(big, n - siz[v]);
    return big;
}

int main(){
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        u--, v--;
        adj[u].pb(v), adj[v].pb(u);
    }
    dfs_init(0, -1);
    vector<pi> nods;
    for (int i = 0; i < n; i++) {
        nods.pb(mp(i, gud(i)));
    }
    sort(all(nods), [&] (pi a, pi b) {
        return a.s < b.s;        
    });
    vi cents;
    for (int i = 0; i < sz(nods); i++) {
        if (i && nods[i].s != nods[i - 1].s) break; 
        cents.pb(nods[i].f);
    }
    cout << nods[0].s << " ";
    cout << sz(cents) << '\n';
    sort(all(cents));
    for (auto x : cents) cout << x + 1 << " ";
}

