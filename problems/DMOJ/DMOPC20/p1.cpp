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
    ll N, S; cin >> N >> S;
    ll tot = (N * (N + 1)) / 2;
    ll diff = tot - S;
    int ans = 0;
    /*
    cout << diff << '\n';
    F0R(i, 1, diff / 2 + 1) {
        if (diff - i <= N && diff - i != i && diff - i != 0) {
            ++ans;
        }
    }
    cout << ans << '\n';
    */
    int ways = (diff + 1) / 2 - 1;
    ways -= max(0LL, ((diff - 1) - N));
    cout << ways << '\n';
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


// 10
// 1 9
// 2 8
// 3 7
// 4 6
// 9
// 1 8
// 2 7
// 3 6
// 4 5
