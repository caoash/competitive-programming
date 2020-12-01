/*
 * Make reductions to realize putting something on a node is just giving sum of neighbor values - previous on path.
 *
 * We can write a DP and then store the best and second best solution to merge the paths by fixing the LCA.
 */

#include <bits/stdc++.h> 
using namespace std;

using ll = long long;

using vi = vector<int>;
using vl = vector<ll>;
using vpl = vector<pair<ll, ll>>;
#define pb push_back
#define rsz resize
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using pi = pair<int,int>;
using pl = pair<ll, ll>;
#define f first
#define s second
#define mp make_pair

const int MX = 100005;
const int MOD = (int) (1e9 + 7);
const ll INF = (ll) 1e18;

int n, m;
vi adj[MX];
ll ans = 0;

ll deg[MX];
ll val[MX];
pl dp[MX][105];
pl dp2[MX][105];
pl fr[MX][105];

void dfs(int v, int p) {
    dp[v][0].f = 0, dp[v][0].s = 0;
    dp[v][1].f = deg[v], dp[v][1].s = 0;
    fr[v][0].f = -1, fr[v][0].s = -1;
    fr[v][1].f = -1, fr[v][1].s = -1;
    for (int to : adj[v]) {
        if (to != p) {
            dfs(to, v);
            for (int s = 0; s <= m; s++) {
                if (dp[to][s].f > dp[v][s].f) {
                    dp[v][s].f = dp[to][s].f;
                    fr[v][s].f = to;
                } 
                if (dp[to][s].s > dp[v][s].s) {
                    dp[v][s].s = dp[to][s].s;
                    fr[v][s].s = to;
                } 
                if (s) {
                    ll go = dp[to][s - 1].f + deg[v] - val[to];
                    if (go > dp[v][s].f) {
                        dp[v][s].f = go;
                        fr[v][s].f = to;
                    } 
                    go = dp[to][s - 1].s + deg[to] - val[v];
                    if (go > dp[v][s].s) {
                        dp[v][s].s = go;
                        fr[v][s].s = to;
                    } 
                }
            }
        }
    }
    for (int to : adj[v]) {
        if (to != p) {
            for (int s = 0; s <= m; s++) {
                if (to != fr[v][s].f) {
                    if (dp[to][s].f > dp2[v][s].f) {
                        dp2[v][s].f = dp[to][s].f;
                    } 
                    if (s) {
                        if (dp[to][s - 1].f != -INF) {
                            ll go = dp[to][s - 1].f + deg[v] - val[to];
                            if (go > dp2[v][s].f) {
                                dp2[v][s].f = go;
                            }
                        }
                    }
                }
                if (to != fr[v][s].s) {
                    if (dp[to][s].s > dp2[v][s].s) {
                        dp2[v][s].s = dp[to][s].s;
                    } 
                    if (s) {
                        ll go = dp[to][s - 1].s + deg[to] - val[v];
                        if (go > dp2[v][s].s) {
                            dp2[v][s].s = go;
                        } 
                    }
                }
            }
        }
    }
    vl p1(m + 1), p2(m + 1);
    p1[0] = dp[v][0].s;
    p2[0] = dp2[v][0].s;
    for (int i = 1; i <= m; i++) {
        p1[i] = max(dp[v][i].s, p1[i - 1]);
        p2[i] = max(dp2[v][i].s, p2[i - 1]);
    }
    for (int i = 0; i <= m; i++) {
        if (fr[v][i].f != fr[v][m - i].s) {
            ans = max(ans, dp[v][i].f + p1[m - i]);
        } else {
            ans = max({ans, dp[v][i].f + p2[m - i], dp2[v][i].f + p1[m - i]});
        }
        ans = max(ans, dp[v][i].f);
        ans = max(ans, dp[v][i].s);
        if (i) ans = max(ans, dp[v][i - 1].s + deg[v]);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m; 
    for (int i = 0; i < n; i++) cin >> val[i];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= m; j++) {
            dp[i][j] = mp(-INF, -INF);
            dp2[i][j] = mp(-INF, -INF);
        }
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        u--, v--;
        deg[u] += val[v];
        deg[v] += val[u];
        adj[u].pb(v), adj[v].pb(u);
    }
    dfs(0, -1);
    cout << ans << '\n';
}

