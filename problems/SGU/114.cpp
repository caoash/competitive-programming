#include <bits/stdc++.h> 
#include <climits>
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
    int n; cin >> n;
    vector<pair<ll, ll>> a(n);
    vector<ll> pref(n), suf(n);
    vector<ll> prefb(n), sufb(n);
    FOR(i, n) {
        cin >> a[i].F >> a[i].S;
    }
    sort(a.begin(), a.end());
    FOR(i, n) {
        pref[i] = (i == 0 ? 0 : pref[i - 1]) + a[i].F * a[i].S;
        prefb[i] = (i == 0 ? 0 : prefb[i - 1]) + a[i].S;
    }
    FORD(i, n) {
        suf[i] = (i == n - 1 ? 0 : suf[i + 1]) + a[i].F * a[i].S;
        sufb[i] = (i == n - 1 ? 0 : sufb[i + 1]) + a[i].S;
    }
    auto tri = [&] (int i) {
        ll pos = a[i].F;
        ll cur = (pos * prefb[i] - pref[i]);
        if (i != n - 1) cur += suf[i + 1] - pos * sufb[i + 1];
        return cur;
    };
    ll ans = 1e18, best = -1; 
    FOR(i, n) { 
        ll cur = tri(i);
        // ll cur = tri(a[i].F);
        if (cur < ans) {
            ans = cur;
            best = a[i].F;
        }
    }
    cout << best << '\n';
}

