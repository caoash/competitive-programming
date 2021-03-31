#include <bits/stdc++.h> 
using namespace std;
 
typedef long long ll;
 
#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)
 
#define F first
#define S second

const ll INF = 1e18;

ll dp[505][505][4];
ll a[505];
int n;

ll solve(int l, int r, int req) {
    if (r < l) return 0;
    else if (dp[l][r][req] != -INF) return dp[l][r][req];
    else {
        if (req == 3) {
            ll res = 0;
            F0R(i, l, r + 1) {
                ll v = i % 3;
                if (i - 1 >= l && i + 1 <= r) {
                    ll cres = solve(l, i - 1, (v + 2) % 3) + solve(i + 1, r, (v + 1) % 3) + a[i];
                    res = max(res, cres);
                }
            }
            return dp[l][r][req] = res;
        } else {
            ll res = -INF;
            F0R(i, l, r + 1) {
                if (i % 3 == req) {
                    ll cres = solve(l, i - 1, 3) + solve(i + 1, r, 3) + a[i];
                    res = max(res, cres);
                }
            }
            return dp[l][r][req] = res;
        }
    }
}
 
int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    cin >> n;
    FOR(i, n) cin >> a[i];
    FOR(i, n) FOR(j, n) FOR(k, 4) dp[i][j][k] = -INF;
    ll ans = solve(0, n - 1, 3);
    cout << ans << '\n';
}

