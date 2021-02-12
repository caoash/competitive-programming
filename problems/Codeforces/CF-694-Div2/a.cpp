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
    int n, x; cin >> n >> x;
    ll sum = 0;
    ll ans2 = 0;
    FOR(i, n) {
        int v; cin >> v;
        sum += v;
        ans2 += ceil((double)v / (double)x);
    }
    sum = ceil((double)sum / (double)x);
    cout << sum << " " << ans2 << '\n';
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

