/*
 * Start by writing the naive DP, which is dp1[length][forward mod][backward mod] = number of values
 * dp2[length][forward mod][backward mod] = sum of values.
 *
 * We can calculate this without too much trouble, using dp1 to calculate dp2.
 *
 * Then we can do D&C DP, since we can merge dp[x][a][b] and dp[y][c][d] for mods a, b, c, d.
 * To do this, let's use contribution to the sum. Assume we have two 4 digit numbers, xxxx and yyyy.
 *
 * Then we can put them together to get xxxxyyyy (we don't need to try yyyyxxxx since any value that can be created one way can be created the other).
 *
 * So, we know that yyyy will appear dp[x][a][b] times and 10^x * xxxx will appear dp[y][c][d] times. So the total contribution would be the sum.
 */

#pragma GCC optimize("unroll-loops")
 
#include <bits/stdc++.h> 
using namespace std;
 
using ll = long long;
 
using vi = vector<int>;
using vl = vector<ll>;
#define pb push_back
#define rsz resize
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
 
using pi = pair<int,int>;
#define f first
#define s second
#define mp make_pair
 
const int mxn = 1000001;
const int mxk = 32;
int n, k, m;
 
struct State {
    int len;
    ll dp[mxk][mxk], dp2[mxk][mxk];
};
 
int pre[mxn][2];
 
State merge(State a, State b) {
    State ret;
    ret.len = a.len + b.len;
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) { 
            if (!a.dp[i][j] || !a.dp2[i][j]) continue;
            for (int i2 = 0; i2 < k; i2++) {
                for (int j2 = 0; j2 < k; j2++) {
                    if (!b.dp[i2][j2] || !b.dp2[i2][j2]) continue;
                    int ni = (i2 + (pre[b.len][0] * i)) % k;
                    int nj = (j + (pre[a.len][0] * j2)) % k;
                    ret.dp[ni][nj] += (a.dp[i][j] * b.dp[i2][j2]) % m;
                    ret.dp2[ni][nj] += (b.dp2[i2][j2] * a.dp[i][j] + a.dp2[i][j] * pre[b.len][1] * b.dp[i2][j2]) % m;
                    if (ret.dp[ni][nj] > m) ret.dp[ni][nj] -= m;
                    if (ret.dp2[ni][nj] > m) ret.dp2[ni][nj] -= m;
                }
            }
        }
    }
    return ret;
}
 
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
gp_hash_table<int, State> calc;
 
State go(int n) {
    if (calc.find(n) != calc.end()) {
        return calc[n];
    }
    else {
        State ans = merge(go(n / 2), go(n / 2));
        if (n & 1) {
            State fin = merge(ans, go(1));
            return calc[n] = fin;
        }
        else {
            return calc[n] = ans;
        }
    }
}
 
int main(){
    ifstream cin("xreverse.in");
    ofstream cout("xreverse.out");
    ios::sync_with_stdio(false);
    cin.tie(0);
    vector<ll> curr(2, 1);
    cin >> n >> k >> m;
    for (int i = 0; i < n; i++) {
        pre[i][0] = curr[0];
        pre[i][1] = curr[1];
        curr[0] *= 10, curr[1] *= 10;
        curr[0] %= k, curr[1] %= m;
    }
    calc[1].len = 1;
    for (int i = 1; i <= 9; i++) {
        calc[1].dp[i % k][i % k]++;
        calc[1].dp2[i % k][i % k] += i;
        calc[1].dp[i % k][i % k] %= m;
        calc[1].dp2[i % k][i % k] %= m;
    }
    State fin = go(n);
    cout << fin.dp2[0][0] << '\n';
}
