/*
 * For min you can greedy for n - 1. For max you can root at centroid and then do DP by directing all towards root or all away.
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

const int MX = 250005;
const int MOD = (int) (1e9 + 7);
const ll INF = (ll) 1e18;

int n;
vi adj[MX];
int sub[MX];
ll init = 0;

void dfs(int v, int p) {
    sub[v] = 1;
    for (int to : adj[v]) {
        if (to != p) {
            dfs(to, v);
            sub[v] += sub[to];
        }
    }
}

void dfs_init(int v, int p) {
    for (int to : adj[v]) {
        if (to != p) {
            dfs_init(to, v);
            init += sub[to];
        }
    }
}

ll comp(int root) {
    init = 0;
    dfs(root, -1);
    map<int, int> vals;
    for (int to : adj[root]) {
        dfs_init(to, root);
        vals[sub[to]]++;
    }
    vector<pi> cv;
    for (auto x : vals) cv.pb(x);
    int dp[2][n + 1];
    memset(dp, -1, sizeof(dp));
    dp[0][0] = 0;
    for (int i = 1; i <= sz(cv); i++) {
        for (int j = 0; j <= n; j++) {
            dp[i & 1][j] = 1e9;
            if (dp[(i & 1) ^ 1][j] >= 0) dp[i & 1][j] = 0;
            else if (j - cv[i - 1].f >= 0 && dp[i & 1][j - cv[i - 1].f] < cv[i - 1].s) {
                if (dp[i & 1][j - cv[i - 1].f] != -1) dp[i & 1][j] = min(dp[i & 1][j], dp[i & 1][j - cv[i - 1].f] + 1);
                else dp[i & 1][j] = -1;
            } else {
                dp[i & 1][j] = -1;
            }
            // dbg(i, j, dp[i & 1][j], cv[i - 1]);
        }
    }
    ll ret = 0;
    // dbg(init);
    for (int i = 1; i < n; i++) {
        if (dp[sz(cv) & 1][i] != -1) {
            // dbg(i, n - i - 1);
            ret = max(ret, (ll)(n - i - 1) * (ll)i + (n - 1) + init);
        }
    }
    return ret;
}

ll mx = 0;
vi cents;

void dfs_solve(int v, int p) {
    bool ok = (n - sub[v]) <= n / 2;
    for (int to : adj[v]) {
        if (to != p) {
            ok &= (sub[to] <= n / 2);
        }
    }
    if (ok) {
        cents.pb(v);
    }
    for (int to : adj[v]) {
        if (to != p) {
            dfs_solve(to, v);
        }
    }
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
    dfs(0, -1);
    dfs_solve(0, -1);
    for (auto x : cents) {
        // dbg(x);
        mx = max(mx, comp(x));
    }
    cout << n - 1 << " " << mx << '\n';
}
