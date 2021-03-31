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
        int n; cin >> n;
        vector<ll> a(n);
        FOR(i, n) cin >> a[i];
        vector<ll> pre(n);
        FOR(i, n) {
            pre[i] = (i == 0 ? 1 : pre[i - 1]) * a[i];
            pre[i] %= 9;
        }
        ll sum = 0;
        FOR(i, n) {
            sum += pre[i];
            sum %= 9;
        }
        if (sum == 0) sum = 9;
        cout << sum << '\n';
    }
}

