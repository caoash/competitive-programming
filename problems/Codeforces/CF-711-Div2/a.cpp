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
    ll n; cin >> n;
    auto gud = [&] (ll cur) {
        ll sum = 0;
        ll at = cur;
        while (at > 0) {
            sum += (at % 10);
            at /= 10;
        }
        return __gcd(cur, sum) > 1;
    };
    while (!gud(n)) ++n;
    cout << n << '\n';
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

