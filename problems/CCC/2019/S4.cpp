#include <bits/stdc++.h> 
using namespace std;

typedef long long ll;

#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)

#define F first
#define S second

const int MX = 1e5;

ll dp[MX][100];

int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, k; cin >> n >> k;
    vector<ll> a(n);
    FOR(i, n) cin >> a[i];
    vector<ll> pre(n), suf(n);
    FOR(i, n) pre[i] = max((i == 0 ? 0 : pre[i - 1]), a[i]);
    FORD(i, n) suf[i] = max((i == n - 1 ? 0 : suf[i + 1]), a[i]);
    if (n == k) {
        cout << pre[n - 1] << '\n';
    } else {
        ll ans = 0;
        FOR(i, n - 1) {
            if (i + 1 <= k && n - i - 1 <= k) {
                ans = max(ans, pre[i] + suf[i + 1]);
            }
        }
        cout << ans << '\n';
    }
    /*
    FOR(i, n) FOR(j, k + 1) dp[i][j] = -1e9;
    dp[0][n % k] = 0;
    FOR(i, n) {
        FOR(j, k + 1) {

        }
    }
    */
}

/*
 * 1 5 2 3 4
 *
 * 1 5 | 2 3 | 4
 *
 * you have ceil(N / K) groups of size <= K, maximize sum of maxes
 *
 * get rid of condition fewest days
 *
 * dp[i][x] = up to endpoint i, s.t if you keep taking K, there will be x left on the last day 
 * it cannot go above K 
 *
 * x = N % K at the start
 */

