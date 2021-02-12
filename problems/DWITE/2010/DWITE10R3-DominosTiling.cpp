#include <bits/stdc++.h> 
using namespace std;

typedef long long ll;

#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)

#define F first
#define S second

ll dp[31][8];
const int MOD = (int) (1e6);

int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    dp[0][0] = 1;
    FOR(i, 31) FOR(j, 8) {
        dp[i][j] %= MOD;
        int nmask = 0;
        FOR(k, 3) {
            if (j & (1 << k)) continue;
            nmask |= (1 << k);
        }
        dp[i + 1][nmask] += dp[i][j];
        if (j == 0) {
            dp[i + 1][1] += dp[i][j];
            dp[i + 1][4] += dp[i][j];
        } else if (j == 1) dp[i + 1][0] += dp[i][j];
        else if (j == 4) dp[i + 1][0] += dp[i][j];
    }
    FOR(qt, 5) {
        int N; cin >> N;
        if (N == 0) cout << 0 << '\n';
        else {
            cout << (dp[N][0] % MOD) << '\n';
        }
    }
}

