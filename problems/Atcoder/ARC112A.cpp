#include <bits/stdc++.h> 
using namespace std;
 
typedef long long ll;
 
#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)
 
#define F first
#define S second

void Solve() {
    ll l, r; cin >> l >> r;
    ll num = r - (2 * l);
    if (num < 0) {
        cout << 0 << '\n';
    } else {
        ll ans = ((num + 1) * (num + 2)) / 2;
        cout << ans << '\n';
    }
}
 
int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);    
    int T; cin >> T;
    while (T--) {
        Solve();
    }
}

/*
 * if A is fixed, answer is A - L
 *
 * 3, 7
 *
 * 3 + 4 = 7
 * 3 + 3 = 6
 * 4 + 3 = 7
 *
 * R - 2 * L, leeway you have
 *
 * 2 ^ (R - 2 * L) 
 *
 * 2 2 4
 * 2 3 5
 * 2 4 6
 * 3 2 5
 * 4 2 6
 * 3 3 6
 *
 *
 * how many B, C are there s.t A + B = C and they are all in range
 *
 * how many pairs, a, b such that a + b = y
 *
 * y + y - 1 ....
 *
 * 
 */
