#include <bits/stdc++.h> 
using namespace std;

typedef long long ll;

#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) for (int i = 0; i < n; i++)

#define F first
#define S second

int dp[205][205];
string s;

int Go(int l, int r) {
    if (dp[l][r] != 1e9) {
        return dp[l][r];
    } else if (r < l) {
        return dp[l][r] = 0;   
    } else {
        F0R(k, l + 1, r + 1) {
            if (s[l] == s[k]) {
                if (l + 1 < k && k - 1 > l) {
                    dp[l][r] = min(dp[l][r], 1 + Go(l + 1, k - 1) + Go(k, r));
                } else {
                    dp[l][r] = min(dp[l][r], Go(k, r));
                }
            }
        }
        dp[l][r] = min(dp[l][r], Go(l + 1, r) + 1 + (l + 1 <= r));
        dp[l][r]++;
        return dp[l][r];
    }
}

void Solve() {
    getline(cin, s);
    int n = (int) s.size();
    FOR(i, n) FOR(j, n) dp[i][j] = 1e9;
    int ans = Go(0, n - 1) + 1;
    cout << ans << '\n';
}

int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T; cin >> T;
    getline(cin, s);
    while (T--) {
        Solve();
    }
}

