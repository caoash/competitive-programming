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
    int n; cin >> n;    
    vector<ll> a(n), b(n), c(n);
    FOR(i, n) cin >> a[i];
    FOR(i, n) cin >> b[i];
    FOR(i, n) c[i] = b[i] - a[i];
    vector<int> ev, od;
    FOR(i, n) {
        if (i % 2) od.push_back(c[i]);
        else ev.push_back(c[i]);
    }
    sort(od.begin(), od.end());
    sort(ev.begin(), ev.end());
    ll ans = 0;
    FOR(i, n) ans += a[i];
    FORD(i, n / 2) {
        if (od[i] + ev[i] > 0) ans += (od[i] + ev[i]);
    }
    cout << ans << '\n';
}

