#include <bits/stdc++.h> 
using namespace std;

typedef long long ll;

#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)

#define F first
#define S second

const int MX = 200005;

/*
 * 1 - start and end in u
 *  - sum of child w/ 2 of dp[c][1] + 2 * len
 * 2 - start in u, end in not u
 *  - fix the subtree you end in, call it x
 *    max value of dp[v][0] - dp[x][0] + dp[x][2]
 * 3 - start in not u, end in not u
 *  - for pair of two diff children dp[c1][2] + dp[c2][2] + d1 + d2 + sum of remaining dp[v][0]
 *    dp[v][0] + dp[c1][2] + dp[c2][2] + d1 + d2 - (dp[c1][0] + 2 * d1) - (dp[c2][0] + 2 * d2)
 *    dp[v][0] + (-dp[c1][0] - d1 + dp[c1][2]) + (-dp[c2][0] - d2 + dp[c2][2])
 *    just take two largest
 *  - same subtree:
 *    for child with 2: sum of dp[v][0] - (dp[c][0] + 2 * d) + (max(dp[c][0], dp[c][1], dp[c][2]) + 2 * d);
 */

struct Edge {
    int e, w;
    bool t;
};

bool big[MX];
vector<Edge> adj[MX];

ll dp1[MX], dp2[MX], dp3[MX];

void dfs(int v, int p) {
    for (auto to : adj[v]) {
        if (to.e != p) {
            dfs(to.e, v);
        }
    }
    for (auto to : adj[v]) {
        if (to.e != p) {
            if (to.t) dp1[v] += (dp1[to.e] + (2 * to.w));
        }
    }
    for (auto to : adj[v]) {
        if (to.e != p) {
            dp2[v] = max(dp2[v], dp1[v] - (to.t ? (dp1[to.e] + 2 * to.w) : 0) + max(dp1[to.e], dp2[to.e]) + to.w);
        }
    }
    ll best = -1e9, ind = -1;
    for (auto to : adj[v]) {
        if (to.e != p) {
            if (to.t) {
                dp3[v] = max(dp3[v], dp1[v] - dp1[to.e] + max({dp1[to.e], dp2[to.e], dp3[to.e]}));
            }
            int cur = dp2[to.e] - to.w - dp1[to.e];
            if (!to.t) cur = dp2[to.e] + to.w;
            if (cur > best) best = cur, ind = to.e;
        }
    }
    ll best2 = -1e9;
    for (auto to : adj[v]) {
        if (to.e != p) {
            int cur = dp2[to.e] - to.w - dp1[to.e];
            if (!to.t) cur = dp2[to.e] + to.w;
            if (cur > best2 && to.e != ind) {
                best2 = cur; 
            }
        }
    }
    if (best != -1e9 && best2 != -1e9) dp3[v] = max(dp3[v], dp1[v] + best + best2);
}

int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, k; cin >> n >> k;
    FOR(i, k) {
        int x; cin >> x;
        big[x - 1] = true;
    }
    FOR(i, n - 1) {
        int u, v, w; cin >> u >> v >> w;
        u--, v--;
        adj[u].push_back({v, w, big[i]});
        adj[v].push_back({u, w, big[i]});
    }
    dfs(0, -1);
    ll ans = 0;
    FOR(i, n) ans = max({ans, dp1[i], dp2[i], dp3[i]});
    cout << ans << '\n';
}

