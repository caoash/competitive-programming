#include <bits/stdc++.h> 
using namespace std;

typedef long long ll;

#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)

#define F first
#define S second

const int MX = 5005;
const int MOD = (int) (1e9 + 7);

ll cnt[MX];
ll dp[MX][MX];
ll coef[MX];

int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, k, q; cin >> n >> k >> q;
    FOR(i, n) cin >> coef[i];
    FOR(i, n) {
        dp[i][0] = 1;
    }
    F0R(j, 1, k + 1) {
        FOR(i, n) {
            if (i) dp[i][j] += dp[i - 1][j - 1];
            dp[i][j] %= MOD;
            if (i + 1 < n) dp[i][j] += dp[i + 1][j - 1];
            dp[i][j] %= MOD;
        }
    }
    FOR(i, n) {
        FOR(j, k + 1) {
            cnt[i] += ((dp[i][j] * dp[i][k - j]) % MOD);
            cnt[i] %= MOD;
        }
    }
    ll sum = 0;
    FOR(i, n) (sum += ((coef[i] * cnt[i]) % MOD)) %= MOD;
    FOR(i, q) {
        ll id, v; cin >> id >> v;
        id--;
        sum -= ((coef[id] * cnt[id]) % MOD);
        if (sum < 0) sum += MOD;
        coef[id] = v;
        (sum += ((coef[id] * cnt[id]) % MOD)) %= MOD;
        cout << sum << '\n';
    }
}

