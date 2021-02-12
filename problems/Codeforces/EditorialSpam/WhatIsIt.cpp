#include <bits/stdc++.h> 
using namespace std;

typedef long long ll;

#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)

#define F first
#define S second


ll sq(ll x) {
    return x * x;
}

void Solve() {
    int n; cin >> n;
    vector<int> res(n);
    iota(res.begin(), res.end(), 1);
    ll ans = 0;
    vector<pair<int, int>> swaps;
    auto swp = [&] (int i, int j) {
        swap(res[i], res[j]);
        ans += sq(j - i);
        swaps.push_back({i, j});
    };
    swp(0, n - 1);
    F0R(i, 1, (n + 1) / 2) {
        swp(i, n - 1);
        if (i != n - i - 1) swp(n - i - 1, 0);
    }
    cout << ans << '\n';
    FOR(i, n) cout << res[i] << " ";
    cout << '\n';
    cout << swaps.size() << '\n';
    reverse(swaps.begin(), swaps.end());
    for (auto x : swaps) {
        cout << x.F + 1 << " " << x.S + 1 << '\n';
    }
}

int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T; cin >> T;
    while(T--) {
        Solve();
    }
}

