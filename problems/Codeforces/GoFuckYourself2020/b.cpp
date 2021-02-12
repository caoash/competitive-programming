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
    vector<int> a(n);
    vector<bool> good(2 * n + 2, false);
    FOR(i, n) cin >> a[i];
    FORD(i, n) {
        if (!good[a[i] + 1]) ++a[i], good[a[i]] = true;
        else good[a[i]] = true;
    }
    int ans = 0;
    F0R(i, 1, 2 * n + 2) if (good[i]) {
        ++ans;
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

