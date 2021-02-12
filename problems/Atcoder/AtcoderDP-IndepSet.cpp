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
const int MOD = (int) (1e9 + 7);

vector<int> adj[MX];
ll dp[MX][2];

void dfs(int v, int p) {
    dp[v][0] = 1, dp[v][1] = 1;
    for (auto to : adj[v]) {
        if (to != p) {
            dfs(to, v);
            (dp[v][0] *= ((dp[to][0] + dp[to][1]) % MOD)) %= MOD;
            (dp[v][1] *= dp[to][0]) %= MOD;
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
        u--; v--;
        adj[u].push_back(v), adj[v].push_back(u);
    }
    dfs(0, -1);
    cout << (dp[0][0] + dp[0][1]) % MOD << '\n';
}

