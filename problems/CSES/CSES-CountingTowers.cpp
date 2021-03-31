#include <bits/stdc++.h> 
using namespace std;
 
typedef long long ll;
 
#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)
 
#define F first
#define S second

const int MOD = (int) (1e9 + 7);

ll dp[(int)(1e6 + 5)][2];
 
int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    dp[1][0] = 1, dp[1][1] = 1;
    F0R(i, 2, 1e6 + 1) {
        dp[i][0] = 2 * dp[i - 1][0] + dp[i - 1][1];
        dp[i][0] %= MOD;
        dp[i][1] = dp[i - 1][0] + 4 * dp[i - 1][1];
        dp[i][1] %= MOD;
    }
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        cout << (dp[n][0] + dp[n][1]) % MOD << '\n';
    }
}

