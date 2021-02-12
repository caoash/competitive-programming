#include <bits/stdc++.h> 
using namespace std;

using ll = long long;

using vi = vector<int>;
using vl = vector<ll>;
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define lb lower_bound
#define ub upper_bound

using pi = pair<int,int>;
#define F first
#define S second
#define mp make_pair

const int MX = 200005;
const int MOD = (int) (1e9 + 7);
const ll INF = (ll) 1e18;

/*
 * char at start of partition must eq char at end of partition for next
 * dp[prefix][prev char][char at start of prev][char at start of curr]
 */

ll dp[MX][4][5][4];
string s;

int main(){
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    cin >> s;
    for (int i = 0; i < sz(s); i++) {
        if (s[i] == 'A') s[i] = '0';
        else if (s[i] == 'G') s[i] = '1';
        else if (s[i] == 'T') s[i] = '2';
        else if (s[i] == 'C') s[i] = '3';
        else s[i] = '4';
    }
    if (s[0] == '4') {
        for (int c = 0; c < 4; c++) {
            dp[1][c][4][c] = 1;
        }
    } else {
        dp[1][s[0] - '0'][4][s[0] - '0'] = 1;
    }
    for (int i = 1; i < sz(s); i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 5; k++) {
                for (int l = 0; l < 4; l++) {
                    dp[i][j][k][l] %= MOD;
                    if (s[i] == '4') {
                        for (int c = 0; c < 4; c++) {
                            if (c != j) {
                                dp[i + 1][c][k][l] += dp[i][j][k][l];
                            }
                            if (k == j || k == 4) dp[i + 1][c][l][c] += dp[i][j][k][l];
                        }
                    } else {
                        if ((s[i] - '0') != j) {
                            dp[i + 1][s[i] - '0'][k][l] += dp[i][j][k][l];
                        }
                        if (k == j || k == 4) dp[i + 1][s[i] - '0'][l][s[i] - '0'] += dp[i][j][k][l];
                    }
                }
            }
        }
    }
    ll ans = 0;
    for (int i = 0; i < 4; i++) for (int j = 0; j < 5; j++) for (int k = 0; k < 4; k++) {
        if (i == j || j == 4) ans += dp[sz(s)][i][j][k], ans %= MOD;
    }
    cout << ans << '\n';
}

