/*
 * Naive DP is like dp[node][len] and then do some combo. Then do naive DP except each tree can't have that many unique path lengths <= y.
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

const int MX = 2505;
const int MOD = (int) (1e9 + 7);
const ll INF = (ll) 1e18;

ll mul(ll a, ll b) {
    return (a * b) % MOD;
}

ll ad(ll a, ll b) {
    return (a + b) % MOD;
}

int n, m, x, y;
vector<pi> adj[MX];
pair<ll, ll> dp[MX][MX];
int dist[MX];
bool vis[MX];
vi order;

void dfs_ord(int v, int p){ 
    vis[v] = true;
    for (auto to : adj[v]) {
        if (to.f != p) {
            dfs_ord(to.f, v);
        }
    }
    order.pb(v);
}

void dfs(int v, int p) {
    for (auto to : adj[v]) {
        if (to.f != p) {
            dist[to.f] = dist[v] + to.s;
            dfs(to.f, v);
        }
    }
}

int cnt = 0;

void solve(int v) {
    ++cnt;
    order.clear();
    dfs_ord(v, -1);
    map<int, pair<ll, ll>> dists;
    for (int i = 0; i < sz(order); i++) {
        int x1 = order[i];
        dist[x1] = 0;
        dfs(x1, -1);
        for (int j = i + 1; j < sz(order); j++) {
            int x2 = order[j];
            auto &to = dists[min(y, dist[x2])];
            to = mp(ad(to.f, 1), ad(to.s, dist[x2]));
        }
    }
    for (int i = 0; i <= y; i++) {
        for (auto x : dists) {
            dp[cnt][min(y, i + x.f)].f = ad(dp[cnt][min(y, i + x.f)].f, mul(x.s.f, dp[cnt - 1][i].f));
            dp[cnt][min(y, i + x.f)].s = ad(dp[cnt][min(y, i + x.f)].s, ad(mul(x.s.s, dp[cnt - 1][i].f), mul(x.s.f, dp[cnt - 1][i].s)));
        }
    }
}

int main(){
    ifstream cin("mooriokart.in");
    ofstream cout("mooriokart.out");
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m >> x >> y;
    memset(vis, false, sizeof(vis));
    for (int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w;
        u--, v--;
        adj[u].pb(mp(v, w)), adj[v].pb(mp(u, w));
    }
    int ccs = n - m;
    y -= x * ccs;
    y = max(y, 0);
    memset(vis, false, sizeof(vis));
    dp[0][0].f = 1;
    for (int i = 0; i < n; i++) {
        if (!vis[i]) solve(i);
    }
    dp[cnt][y].s = ad(dp[cnt][y].s, mul(dp[cnt][y].f, mul(x, ccs)));
    for (int i = 0; i < ccs - 1; i++) dp[cnt][y].s = mul(dp[cnt][y].s, (ll)2);
    for (int i = 1; i < ccs; i++) dp[cnt][y].s = mul(dp[cnt][y].s, (ll)i);
    cout << dp[cnt][y].s << '\n';
}

