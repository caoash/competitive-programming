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

ll deg[MX];
vector<int> adj[MX];
ll dp[MX], fr[MX];
ll ans = -1e9;

void dfs(int v, int p) {
    for (int to : adj[v]) {
        if (to != p) {
            dfs(to, v);
            if (dp[to] + deg[v] > dp[v]) {
                dp[v] = dp[to] + deg[v];
                fr[v] = to;
            }
        }
    }
    ans = max(ans, dp[v] + 2);
    dp[v] = max(dp[v], deg[v]);
}

void dfs2(int v, int p) {
    ll best = -1e9;
    for (int to : adj[v]) {
        if (to != p && to != fr[v]) {
            best = max(best, dp[to]);
        }
    }
    ans = max(ans, dp[v] + best + 2);
    for (int to : adj[v]) {
        if (to != p) {
            dfs2(to, v);
        }
    }
}

int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    FOR(i, n - 1) {
        int u, v; cin >> u >> v;
        u--, v--;
        adj[u].push_back(v), adj[v].push_back(u);
        deg[u]++, deg[v]++;
    }
    FOR(i, n) deg[i] -= 2;
    FOR(i, n) dp[i] = -1e9, fr[i] = -1;
    dfs(0, -1);
    dfs2(0, -1);
    cout << ans << '\n';
}

