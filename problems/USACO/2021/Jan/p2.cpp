#include <bits/stdc++.h> 
using namespace std;

typedef long long ll;

#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)

#define F first
#define S second

ll dp[2005][2005];

int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m; cin >> n >> m;
    FOR(i, n) FOR(j, m) dp[i][j] = 1e9;
    vector<ll> c(m);
    FOR(i, m) cin >> c[i];
    dp[0][0] = 0;
    FOR(i, n) FOR(j, m) {
        if (j) dp[i][j] = min(dp[i][j], dp[i][j - 1] + ((i + 1) * (i + 1)));
        if (i) dp[i][j] = min(dp[i][j], dp[i - 1][j] + c[j]);
    }
    int q; cin >> q;
    FOR(i, q) {
        int x, y; cin >> x >> y;
        x--, y--;
        cout << dp[x][y] << '\n';
    }
}

