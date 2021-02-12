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
    vector<pair<ll, ll>> a(n);
    FOR(i, n) {
        cin >> a[i].F;
        a[i].S = a[i].F;
    }
    ll ans = 0;
    bool stop = false;
    int i = 0;
    while (!stop) {
        int v = a[i].F;
        ans += v;
        if (!stop) {
            if (a[i].S % x == 0) {
                a.push_back({a[i].F, a[i].S / x});
            } else {
                stop = true;
            }
        }
        ++i;
    }
    while (i < a.size()) ans += a[i++].F;
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

