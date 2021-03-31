#include <bits/stdc++.h> 
using namespace std;
 
typedef long long ll;
 
#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)
 
#define F first
#define S second

ll dp[65][65];
 
ll Solve(int l, int r) {
    if (dp[l][r] != -1) {
        return dp[l][r];
    } else if (r < l) {
        return 1;
    } else {
        ll sum = 0;
        F0R(x, l + 1, r + 1) {
            ll fans = 1;
            ll sans = 1;
            fans = Solve(l + 1, x - 1);
            sans = Solve(x + 1, r);
            sum += fans * sans;
        }
        return dp[l][r] = sum;
    }
}

int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);    
    int k; cin >> k;
    k *= 2;
    FOR(i, k + 1) FOR(j, k + 1) dp[i][j] = -1;
    ll ans = Solve(0, k - 1);
    cout << ans << " " << (k / 2) + 1 << '\n';
}

