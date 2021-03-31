#include <bits/stdc++.h> 
using namespace std;
 
typedef long long ll;
 
#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)
 
#define F first
#define S second

const int MX = 1005;

ll dp[MX][2];

void Solve(int tc) {
    ll x, y; cin >> x >> y;
    string s; cin >> s;
    dp[0][0] = 0, dp[0][1] = 0;
    F0R(i, 1, s.size() + 1) {
        dp[i][0] = 1e18, dp[i][1] = 1e18;
        if (s[i - 1] == 'C') {
            dp[i][0] = min(dp[i - 1][1] + y, dp[i - 1][0]);
        } else if (s[i - 1] == 'J') {
            dp[i][1] = min(dp[i - 1][1], dp[i - 1][0] + x);
        } else {
            dp[i][0] = min(dp[i - 1][1] + y, dp[i - 1][0]);
            dp[i][1] = min(dp[i - 1][1], dp[i - 1][0] + x);
        }
    }
    cout << "Case #" << tc << ": " << min(dp[s.size()][0], dp[s.size()][1]) << '\n';
}
 
int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);    
    int T; cin >> T;
    int tt = 0;
    while (T--) {
        Solve(++tt);
    }
}

