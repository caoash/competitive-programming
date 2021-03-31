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
    int n, k; cin >> n >> k;
    int meet = 0;
    if (n % 2 == 1) {
        meet += ((k - 1) / (n / 2));
    }
    int fin = (((k - 1) + meet) % n) + 1;
    cout << fin << '\n';
}
 
int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    int T; cin >> T;
    while (T--) {
        Solve();
    }
}

/*
 * 1 2 3 4
 * 1 2 3 4 5
 * if n even, they'll never meet
 * otherwise, they meet at:
 * n / 2, n, n + n / 2, etc
 * k / (n / 2)
 */

