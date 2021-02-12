#include <bits/stdc++.h> 
using namespace std;

typedef long long ll;

#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)

#define F first
#define S second

ll dp[(int) (1e5 + 5)];
bool vis[(int) (1e5 + 5)];

int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll H; cin >> H;
    H--;
    ll a, b, c; cin >> a >> b >> c;
    FOR(i, c) dp[i] = 1e18;
    dp[0] = 0;
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> nxt;
    nxt.push({0, 0});
    while (!nxt.empty()) {
        auto cur = nxt.top();
        nxt.pop();
        int i = cur.S;
        if (vis[i]) continue;
        int nxa = (i + a);
        while (nxa >= c) nxa -= c;
        int nxb = i + b;
        while (nxb >= c) nxb -= c;
        if (dp[i] + a <= H && !vis[nxa]) {
            if (dp[nxa] > dp[i] + a) {
                dp[nxa] = dp[i] + a;
                nxt.push({dp[nxa], nxa});
            }
        }
        if (dp[i] + b <= H && !vis[nxb]) {
            if (dp[nxb] > dp[i] + b) {
                dp[nxb] = dp[i] + b;
                nxt.push({dp[nxb], nxb});
            }
        }
        vis[i] = true;
    }
    ll ans = 0;
    FOR(i, c) {
        if (dp[i] != 1e18) {
            ans += ((H - dp[i]) / c) + 1;
        }
    }
    cout << ans << '\n';
}

