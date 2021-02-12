#include <bits/stdc++.h> 
using namespace std;

typedef long long ll;

#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)

#define F first
#define S second

const int MOD = (int) (1e9 + 7);

int n, k, q;
int s, t, bs, bt;

ll dp[65][65][65];
ll dp2[65][(1 << 15)];
int adj[65][65];

ll Solve(int u, int v, int x) {
    if (dp[u][v][x] != -1) {
        return dp[u][v][x];
    } else if (x == 0) {
        return dp[u][v][x] = (adj[u][v]);
    } else {
        ll sum = 0;
        sum += Solve(u, v, x - 1);
        FOR(mid, n) {
            sum += (Solve(u, mid, x - 1) * Solve(mid, v, x - 1));
            sum %= MOD;
        }
        return dp[u][v][x] = sum;
    }
}

void Small() {
    auto res = [&] (int dest, int last, int st, int fir) {
        ll ans = 0;
        FOR(i, n) FOR(j, (1 << k)) {
            if (i == dest && (j & (1 << last)) && dp2[i][j] != -1) {
                ans += dp2[i][j];
            }
        }
        ans %= MOD;
        return (ans + (st == dest && fir == last)) % MOD;
    };
    FOR(tr, q) {
        cin >> bs >> s >> bt >> t;
        bs--, bt--, s--, t--;
        memset(dp2, 0, sizeof(dp2));
        FOR(i, n) if (adj[s][i]) {
            dp2[i][((1 << k) - 1) ^ (1 << bs)] = 1;
        }
        FORD(j, (1 << k)) {
            FOR(i, n) {
                if (dp2[i][j]) {
                    dp2[i][j] %= MOD;
                    FOR(to, n) {
                        if (adj[i][to]) {
                            FOR(l, k) {
                                if (j & (1 << l)) {
                                    int nmask = (j ^ (1 << l)) | ((1 << l) - 1);
                                    dp2[to][nmask] += dp2[i][j];
                                    dp2[to][nmask] %= MOD;
                                }
                            }
                        }
                    }
                }
            }
        }
        cout << res(t, bt, s, bs) << '\n';
    }
}

void Big() {
    memset(dp, -1, sizeof(dp));
    FOR(i, q) {
        cin >> bs >> s >> bt >> t;
        s--, t--;
        ll cur = Solve(s, t, k - 2);
        cout << cur << '\n';
    }
}

int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> k >> q;
    FOR(i, n) {
        string g; cin >> g;
        FOR(j, n) {
            adj[i][j] = (g[j] - '0');
        }
    }
    if (k <= 15) Small();
    else Big();
}

