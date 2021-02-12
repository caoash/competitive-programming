#include <bits/stdc++.h> 
using namespace std;

typedef long long ll;

#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)

#define F first
#define S second

set<pair<int, int>> vals;

ll dp[(int) (1e6 + 5)];

int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll s, p, m;
    int n; cin >> s >> p >> m >> n;
    vector<int> a(n);
    FOR(i, n) {
        int v; cin >> v;
        vals.insert({v, i});
        a[i] = v;
        dp[i] = (ll) (1e18);
    }
    FOR(i, n) {
        ll pos = a[i];
        ll prev = max(pos - m + 1, 0LL);
        auto it = vals.lower_bound(make_pair(prev, INT_MIN));
        ll trans = 0;
        if (it != vals.begin()) {
            --it;
            trans = dp[it->S];
        }
        dp[i] = min(dp[i], trans + p);
        ll go = (i == 0 ? 0 : dp[i - 1]);
        dp[i] = min(dp[i], go + s);
        // cout << i << " " << dp[i] << '\n';
    }
    cout << dp[n - 1] << '\n';
}

