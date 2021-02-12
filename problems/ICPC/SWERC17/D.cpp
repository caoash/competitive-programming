#include <bits/stdc++.h> 
using namespace std;

typedef long long ll;

#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) for (int i = 0; i < n; i++)

#define F first
#define S second

ll dp[55][55]; //dp[l][r] = fullclear
ll dp2[405][55][55][55]; //dp[what is ti][start index][first i][first j of ti]
ll dp3[55][55]; //dp[l][r] = max points not always fullclear

int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    string s;
    cin >> s;
    int n = (int) s.size();
    int m; cin >> m;
    vector<pair<string, int>> vals;
    FOR(i, m) {
        string g; int v;
        cin >> g >> v;
        vals.push_back({g, v});
        reverse(g.begin(), g.end());
        vals.push_back({g, v});
    }
    memset(dp, -0x3f3f3f, sizeof(dp));
    memset(dp2, -0x3f3f3f, sizeof(dp2));
    FOR(i, n) FOR(j, n) if (j < i) dp[i][j] = 0;
    m *= 2;
    F0R(len, 1, n + 1) {
        FOR(j, n) {
            int st = j, en = j + len - 1;
            if (en >= n) continue;
            int idx = en - st + 1;
            FOR(k, m) {
                dp2[k][st][0][0] = 0;
                string &curr = vals[k].F;
                int sz = (int) curr.size();
                F0R(j2, 1, sz + 1) {
                    FOR(prev, idx) {
                        if (curr[j2 - 1] == s[en]) {
                            dp2[k][st][idx][j2] = max(dp2[k][st][idx][j2], dp2[k][st][prev][j2 - 1] + (en > 0 ? dp[st + prev][en - 1] : 0));
                        }
                    }
                }
                F0R(i2, st, en + 1) {
                    dp[st][en] = max(dp[st][en], dp2[k][st][i2 - st + 1][sz] + (i2 < n ? 0 : dp[i2 + 1][en]) + vals[k].S);
                }
            }
        }
    }
    F0R(len, 1, n + 1) {
        FOR(j, n) {
            int st = j, en = j + len - 1;
            if (en >= n) continue;
            F0R(l, st, en + 1) {
                F0R(r, l, en + 1) {
                    dp3[st][en] = max(dp3[st][en], (l > 0 ? dp3[st][l - 1] : 0) + dp[l][r] + (r < n ? 0 : dp3[r + 1][en]));
                }
            }
        }
    }
    cout << dp3[0][n - 1] << '\n';
}

