#include <bits/stdc++.h> 
using namespace std;

typedef long long ll;

#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)

#define F first
#define S second

const int YUUUUGE = 1e5;

ll dp[2][YUUUUGE];

void Solve() {
    int n, m; cin >> n >> m;
    vector<pair<int, ll>> vals;
    FOR(i, n) {
        int w; ll v; cin >> w >> v;
        vals.push_back({w, v});
    }
    FOR(i, m) {
        int w; ll v; cin >> w >> v;
        vals.push_back({-w, v});
    }
    srand(time(0));
    random_shuffle(vals.begin(), vals.end());
    FOR(i, 2) FOR(j, YUUUUGE) dp[i][j] = -1e18;
    dp[0][YUUUUGE / 2] = 0;
    F0R(i, 1, n + m + 1) {
        FOR(j, YUUUUGE) {
            dp[i & 1][j] = max(dp[i & 1][j], dp[(i & 1) ^ 1][j]);
            if (j - vals[i - 1].F >= 0 && j - vals[i - 1].F < YUUUUGE) {
                dp[i & 1][j] = max(dp[i & 1][j], dp[(i & 1) ^ 1][j - vals[i - 1].F] + vals[i - 1].S);
            }
        }
    }
    ll ans = dp[(n + m) & 1][YUUUUGE / 2];
    cout << max(ans, 0LL) << '\n';
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

