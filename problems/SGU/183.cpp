#include <bits/stdc++.h> 
using namespace std;
 
typedef long long ll;
 
#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)
 
#define F first
#define S second

int dp[2][105][105];

int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);    
    int n, m; cin >> n >> m;
    vector<int> a(n);
    FOR(i, n) cin >> a[i];
    FOR(i, 2) FOR(j, m + 1) FOR(k, m + 1) dp[i][j][k] = 1e9;
    FOR(i, m - 1) F0R(j, i + 1, m) {
        dp[(m - 1) & 1][j][i] = a[m - i - 1] + a[m - j - 1];
    }
    F0R(i, m, n) {
        FOR(j, m - 1) {
            F0R(k, j + 1, m) {
                dp[i & 1][k][j] = 1e9;
                if (j == 0) {
                    F0R(l, k, m) {
                        dp[i & 1][k][j] = min(dp[i & 1][k][j], dp[(i & 1) ^ 1][l][k - 1] + a[i]);
                    }
                } else {
                    dp[i & 1][k][j] = min(dp[i & 1][k][j], dp[(i & 1) ^ 1][k - 1][j - 1]);
                }
            }
        }
    }
    int ans = 1e9;
    FOR(i, m) F0R(j, i + 1, m + 1) {
        ans = min(ans, dp[(n - 1) & 1][j][i]); 
    }
    cout << ans << '\n';
}

