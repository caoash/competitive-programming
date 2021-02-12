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

ll dp[105][MX];

int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, k, m; cin >> n >> k >> m;
    dp[0][0] = 1;
    FOR(i, n) {
        FOR(j, MX) {
            if (dp[i][j] > m) dp[i][j] -= m;
            dp[i + 1][j] += dp[i][j];
            if (dp[i + 1][j] > m) dp[i + 1][j] -= m;
            F0R(c, 1, k + 1) {
                ll ad = (i + 1) * c;
                if (j + ad < MX) {
                    dp[i + 1][j + ad] += dp[i][j];
                    if (dp[i + 1][j + ad] > m) dp[i + 1][j + ad] -= m;
                }
            }
        }
    }
    F0R(x, 1, n + 1) {
        ll ret = 0;
        FOR(j, MX) {
            ret += (((ll)(k + 1) * (ll)(dp[x - 1][j]) % m) * dp[n - x][j]) % m;
            if (ret > m) ret -= m;
        }
        ll ans = (ret - 1) + m;
        if (ans > m) ans -= m;
        cout << ans << '\n';
    }
}

