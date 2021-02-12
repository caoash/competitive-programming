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
    int n, q, k; cin >> n >> q >> k;
    vector<int> a(n);
    for (auto &x : a) cin >> x;
    vector<ll> ps(n);
    ps[0] = 0;
    F0R(i, 1, n - 1) {
        ll vi = a[i + 1] - a[i - 1] - 2;
        ps[i] = ps[i - 1] + vi;
    }
    auto qry = [&] (int l, int r) {
        if (r < l) return 0LL;
        return ps[r] - (l == 0 ? 0LL : ps[l - 1]);
    };
    FOR(i, q) {
        int l, r; cin >> l >> r;
        l--, r--;
        if (l == r) {
            cout << k - 1 << '\n';
        } else {
            ll bord = (k - a[r - 1] - 1) + (a[l + 1] - 2);
            ll ans = bord + qry(l + 1, r - 1);
            cout << ans << '\n';
        }
    }
}

