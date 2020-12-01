/*
 * Solve for the two trees separately, then pair them greedily.
 *
 * To solve you notice that collisions increase the depth of one of them by 1, so store the depths
 * and greedily change them.
 *
 * However, this gets MLE on 2tc even after a lot of optimizations. 
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

const int MX = 1000000;
const int MOD = (int) (1e9 + 7);
const ll INF = (ll) 1e18;

int n, w, z;
vi adj[MX];
bitset<MX> st;
pi sep = mp(-1, -1);
vi deps[2];

pi dfs(int v, int p) {
    int s1 = 0, s2 = 0;
    s1 += (v < w);
    s2 += (v >= n - z && v < n);
    for (int to : adj[v]) {
        if (to != p) {
            pi nxt = dfs(to, v);
            s1 += nxt.f, s2 += nxt.s;
        }
    }
    if (s1 == w && s2 == 0) sep = mp(v, p);
    else if (s2 == z && s1 == 0) sep = mp(p, v);
    return mp(s1, s2);
}

void dfs_dep(int v, int p, int x, int d) {
    for (int to : adj[v]) {
        if (to != p) {
            dfs_dep(to, v, x, d + 1);
        }
    }
    if (x == 1) adj[v].clear();
    if (x == 0 && st[v]) deps[x].pb(d);
    else if (x == 1 && v >= n - z && v < n) deps[x].pb(d);
    
}

int main(){
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> w >> z;
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        u--, v--;
        adj[u].pb(v), adj[v].pb(u);
    }
    int m; cin >> m;
    for (int i = 0; i < m; i++) {
        int x; cin >> x;
        x--;
        st[x] = 1;
    }
    dfs(0, -1);
    assert(sep.f != -1);
    dfs_dep(sep.f, sep.s, 0, 0);
    dfs_dep(sep.s, sep.f, 1, 0);
    sort(all(deps[0]));
    sort(all(deps[1]));
    for (int i = 1; i < sz(deps[0]); i++) {
        if (deps[0][i] <= deps[0][i - 1]) deps[0][i] = deps[0][i - 1] + 1;
        assert(deps[0][i] > deps[0][i - 1]);
    }
    reverse(all(deps[0]));
    int ans = 0;
    for (int i = 0; i < sz(deps[0]); i++) {
        ans = max(ans, deps[0][i] + deps[1][i] + 1);
    }
    cout << ans << '\n';
}
