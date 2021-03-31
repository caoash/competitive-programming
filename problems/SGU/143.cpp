#include <bits/stdc++.h> 
using namespace std;
 
typedef long long ll;
 
#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)
 
#define F first
#define S second
const int MX = 16005;

vector<int> adj[MX];
ll a[MX], dp[MX], sub[MX];

void dfs(int v, int p) {
    dp[v] = a[v];
    for (int to : adj[v]) {
        if (to != p) {
            dfs(to, v);
            dp[v] += max(dp[to], 0LL);
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
    FOR(i, n) {
        cin >> a[i];
    }
    FOR(i, n - 1) {
        int u, v; cin >> u >> v;
        u--, v--;
        adj[u].push_back(v), adj[v].push_back(u);
    }
    dfs(0, -1);
    ll ans = -1e18;
    FOR(i, n) {
        ans = max(ans, dp[i]); 
    }
    cout << ans << '\n';
}

