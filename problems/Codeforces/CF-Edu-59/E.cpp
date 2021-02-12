#include <bits/stdc++.h> 
using namespace std;
 
typedef long long ll;
 
#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) for (int i = 0; i < n; i++)
 
#define F first
#define S second

ll dp[105][105]; //dp[l][r] = fullclear
ll dp2[2][105][105][105]; //dp[what is ti][start index][first i][first j of ti]
int dat[105];
 
int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    string s;
    cin >> s;
    FOR(i, n) cin >> dat[i];
    FOR(i, 2) FOR(j, n + 1) FOR(k, n + 1) FOR(l, n + 1) dp2[i][j][k][l] = -1e18;
    FOR(i, n) FOR(j, n) dp[i][j] = -1e18;
    FOR(i, n) FOR(j, n) if (j < i) dp[i][j] = 0;
    F0R(len, 1, n + 1) {
        FOR(j, n) {
            int st = j, en = j + len - 1;
            if (en >= n) continue;
            int idx = en - st + 1;
            dp2[0][st][0][0] = 0;
            dp2[1][st][0][0] = 0;
            int dig = s[en] - '0';
            F0R(j2, 1, n + 1) {
                FOR(prev, idx) {
                    dp2[dig][st][idx][j2] = max(dp2[dig][st][idx][j2], dp2[dig][st][prev][j2 - 1] + (en > 0 ? dp[st + prev][en - 1] : 0));
                }
            }
            F0R(i2, st, en + 1) {
                F0R(j2, st, en + 1) {
                    dp[st][en] = max(dp[st][en], dp2[dig][st][i2 - st + 1][j2 - st + 1] + (i2 < n ? 0 : dp[i2 + 1][en]) + dat[j2 - st]);
                }
            }
        }
    }
    cout << dp[0][n - 1] << '\n';
}
 
