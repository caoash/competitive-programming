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
    int n, m; cin >> n >> m;
    vector<int> k(n);
    vector<int> c(m);
    FOR(i, n) cin >> k[i], k[i]--;
    sort(k.begin(), k.end());
    FOR(i, m) cin >> c[i];
    vector<int> ans(n);
    FOR(i, n) ans[i] = c[k[i]];
    int p1 = n - 1, p2 = 0;
    while (p1 >= 0 && p2 < m) {
        if (c[p2] < ans[p1] && p2 <= k[p1]) {
            ans[p1] = c[p2];
            ++p2, --p1;
        } else {
            ++p2;
        }
    }
    ll sum = 0;
    FOR(i, n) sum += ans[i];
    cout << sum << '\n';
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
/*
 * 2 2 3 3 4
 *
 * 5 5 3 5 12
 *
 * 3 5 12 20
 *
 *
 * 10 10 40 90 160 
 *
 *
 */

