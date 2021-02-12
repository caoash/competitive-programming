#include <bits/stdc++.h> 
using namespace std;

typedef long long ll;

#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)

#define F first
#define S second

const int MX = 100005;

vector<int> adj[MX];
double a[MX], b[MX];
double diffs[MX];
double dp[MX];
int n;

const double EPS = 1e-9;

void dfs_dp(int v, int p) {
    dp[v] = diffs[v];
    for (int to : adj[v]) {
        if (to != p) {
            dfs_dp(to, v);
            dp[v] += dp[to];
        }
    }
    if (v != 0) dp[v] = max(dp[v], 0.0);
}

bool works(double mid) {
    FOR(i, n) diffs[i] = (a[i] - (mid * b[i]));
    FOR(i, n) dp[i] = -1e9;
    dfs_dp(0, -1);
    return (dp[0] >= 0);
}

int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    FOR(i, n) cin >> a[i];
    FOR(i, n) cin >> b[i];
    FOR(i, n - 1) {
        int u, v; cin >> u >> v;
        u--, v--;
        adj[u].push_back(v), adj[v].push_back(u);
    }
    double lo = 0, hi = 1e9;
    double ans = 0;
    while (lo <= hi) {
        double mid = (lo + hi) / 2;
        if (works(mid)) {
            lo = mid + EPS;
            ans = mid;
        } else {
            hi = mid - EPS;
        }
    }
    cout << fixed << setprecision(6) << ans << '\n';
}
