#include <bits/stdc++.h> 
using namespace std;

typedef long long ll;
typedef long double ld;

#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)

#define F first
#define S second

const ld EPS = 1e-6;

int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m; cin >> n >> m;
    vector<ll> c(m);
    FOR(i, m) cin >> c[i];
    // for (i, j)
    // (j + c[j] * i)
    int q; cin >> q;
    FOR(i, q) {
        ll x, y; cin >> x >> y;
        x--, y--;
        ll ans = (ll) (1e18);
        auto f = [&] (ld j) {
            ll fj = (c[0] * j) + (c[y] * (x - j)) + (y * (j + 1) * (j + 1));
            return fj;
        };
        // vector<ll> diffs;
        FOR(j, x + 1) {
            // diffs.push_back(f(j + 1) - f(j));
        }
        /*
        FOR(j, diffs.size() - 1) {
            assert(diffs[j + 1] >= diffs[j]);
        }
        */
        ld lo = 0, hi = x;
        while (hi - lo >= EPS) {
            ld mid1 = lo + (hi - lo) / 3;
            ld mid2 = hi - (hi - lo) / 3;
            if (f(mid1) < f(mid2)) {
                lo = mid1 + 1;
            } else {
                hi = mid2 - 1;
            }
            ans = min(ans, f(mid1));
            ans = min(ans, f(mid2));
        }
        cout << ans << '\n';
    };
}

