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
    int n, m; cin >> n >> m;
    vector<int> a(n);
    FOR(i, n) cin >> a[i];
    int ca = 0;
    FOR(i, n) ca += a[i];
    if (ca <= 0) {
        cout << 0 << '\n';
        return 0;
    }
    FOR(i, m) {
        int x; cin >> x;
        x--;
        ca -= a[x];
        a[x] ^= 1;
        ca += a[x];
        if (ca <= i + 1) {
            cout << i + 1 << '\n';
            return 0;
        }
    }
    cout << ca << '\n';
}

