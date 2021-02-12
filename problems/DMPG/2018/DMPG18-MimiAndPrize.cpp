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

vector<int> adj[MX];

ll dp[MX], dp2[MX];
int a[MX];
ll ans = 0;

void dfs(int v, int p) {
    int pt = (a[v] % 2);
    if (pt % 2) dp[v] = 1;
    dp2[v] = 1;
    for (auto to : adj[v]) {
        if (to != p) {
            dfs(to, v);
            if ((a[to] % 2) == (pt ^ 1)) {
                dp[v] += dp[to];
                dp2[v] += dp2[to];
            }
        }
    }
    ans += dp[v];
    if (pt % 2) ans += dp2[v] - 1;
    for (auto to : adj[v]) {
        if (to != p) {
            if ((a[to] % 2) == (pt ^ 1)) {
                ans += ((dp[v] - pt) * dp2[to]);
                ans -= (dp[to] * dp2[to]);
            }
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
    FOR(i, n) cin >> a[i];
    FOR(i, n - 1) {
        int u, v; cin >> u >> v;
        u--, v--;
        adj[u].push_back(v), adj[v].push_back(u);
    }
    dfs(0, -1);
    cout << ans << '\n';
}

