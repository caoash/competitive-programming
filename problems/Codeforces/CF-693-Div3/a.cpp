#include <bits/stdc++.h> 
using namespace std;

typedef long long ll;

#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)

#define F first
#define S second

int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T; cin >> T;
    while (T--) {
        int w, h, n; cin >> w >> h >> n;
        ll a = 1, b = 1;
        while (w % 2 == 0) {
            w /= 2; 
            a *= 2;
        }
        while (h % 2 == 0) {
            h /= 2;
            b *= 2;
        }
        if (a * b >= n) cout << "YES\n";
        else cout << "NO\n";
    }
}

