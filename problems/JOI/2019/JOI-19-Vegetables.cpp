/*
 * Observe that you can view swaps as "insertions" and you only insert from right to left.
 *
 * Then, let's try to build the string by performing some insertions. Note that at some point, you want to use the
 * leftmost r/g/y not yet used.
 *
 * Let dp[r][g][y][c] = minimum number of swaps needed to build a string with r reds, g greens, and y yellows such that the last color was c.
 *
 * Then, we can just build the string by transitioning over the next color and making sure there aren't duplicates.
 *
 * The number of swaps needed to add a color can be computed with prefix sums.
 */

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
#define f first
#define s second
#define mp make_pair

const int MX = 200005;
const int MOD = (int) (1e9 + 7);
const ll INF = (ll) 1e18;

int n;

int dp[405][405][405][3];
int pos[405][3];
int psum[405][3];

int main(){
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    string s; cin >> s;
    string al = "RGY";
    int cnts[3];
    for (int i = 0; i < 3; i++) {
        pos[0][i] = -1;
        int c = 1;
        for (int j = 0; j < n; j++) {
            if (j != 0) psum[j][i] = psum[j - 1][i];
            if (s[j] == al[i]) {
                pos[c++][i] = j; 
                psum[j][i]++;
            }
        }
        cnts[i] = c - 1;
    }
    auto qry = [&] (int l, int r, int t) {
        if (r < l) return 0;
        if (l == 0) return psum[r][t];
        else return psum[r][t] - psum[l - 1][t];
    };
    for (int i = 0; i <= cnts[0]; i++) 
    for (int j = 0; j <= cnts[1]; j++) 
    for (int k = 0; k <= cnts[2]; k++) {
        dp[i][j][k][0] = 1e9;
        dp[i][j][k][1] = 1e9;
        dp[i][j][k][2] = 1e9;
    }
    dp[0][0][0][0] = 0;
    dp[0][0][0][1] = 0;
    dp[0][0][0][2] = 0;
    for (int i = 0; i <= cnts[0]; i++) {
        for (int j = 0; j <= cnts[1]; j++) {
            for (int k = 0; k <= cnts[2]; k++) {
                for (int p = 0; p < 3; p++) {
                    if (i != cnts[0] && p != 0) {
                        int add = qry(pos[j][1] + 1, pos[i + 1][0], 1) + qry(pos[k][2] + 1, pos[i + 1][0], 2);
                        dp[i + 1][j][k][0] = min(dp[i + 1][j][k][0], dp[i][j][k][p] + add);
                    }
                    if (j != cnts[1] && p != 1) {
                        int add = qry(pos[i][0] + 1, pos[j + 1][1], 0) + qry(pos[k][2] + 1, pos[j + 1][1], 2);
                        dp[i][j + 1][k][1] = min(dp[i][j + 1][k][1], dp[i][j][k][p] + add);
                    }
                    if (k != cnts[2] && p != 2) {
                        int add = qry(pos[i][0] + 1, pos[k + 1][2], 0) + qry(pos[j][1] + 1, pos[k + 1][2], 1);
                        dp[i][j][k + 1][2] = min(dp[i][j][k + 1][2], dp[i][j][k][p] + add);
                    }
                }
            }
        }
    }
    int ans = INT_MAX;
    for (int p = 0; p < 3; p++) ans = min(ans, dp[cnts[0]][cnts[1]][cnts[2]][p]);
    if (ans == 1e9) {
        cout << -1 << '\n';
    } else {
        cout << ans << '\n';
    }
}
