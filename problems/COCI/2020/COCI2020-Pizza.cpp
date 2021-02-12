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
    freopen("a.3.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    set<int> a;
    FOR(i, n) {
        int x; cin >> x;
        a.insert(x);
    }
    int ans = 0;
    int k; cin >> k;
    FOR(i, k) {
        int ki; cin >> ki;
        bool good = true;
        FOR(j, ki) {
            int y; cin >> y;
            good &= (!a.count(y));
        }
        ans += good;
    }
    cout << ans << '\n';
}

