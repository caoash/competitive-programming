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
    int n; cin >> n;
    vector<ll> a(n);
    FOR(i, n) cin >> a[i];
    ll ans = 0;
    FORD(i, n) {
        if (i + a[i] < n) {
            a[i] += a[i + a[i]];
        }
        ans = max(ans, a[i]);
    }
    cout << ans << '\n';
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

