/*
 * Observe the problem is asking for the number of permutations that start with some number and end with some number b
 * in the form a[0] > a[1] < a[2] > a[3] ... or a[0] < a[1] > a[2] < a[3]...
 *
 * Let dp[i][j] represent the number of permutations which work using numbers 1 ... i and forming j connected components. We'll
 * say that a connected component is something like 12..3..4, where the .. represent 1 or more values. Then, if you place the
 * elements in increasing order, you can make some observations.
 *
 * a.) If you place an element that is not a or b, you can place it in some empty space (denoted as ..) and either:
 *  1. merge it with the left and right ccs, like 12..3 => 1243 if you're placing 4, since it will alternate
 *  2. create a new connected component, so like 12..3 => 12..4..3 if you're placing 4. If a or b are already placed, they
 *  need to be on the ends, so you can't make the new cc at the ends.
 *  3. realize you can't merge with one connected component, for example if you have ..3.. you can't place 4 and have ..34.. 
 *  since we assume the element isn't a or b, so then when you have to place a or b on the ends they'll be greater and create
 *  something like ...346.. which is invalid.
 * b.) If you place an element that is a or b, you can only place them at the start / end and either:
 *  1. merge with the one after, so like ..2.. => 12..
 *  2. create a new connected component, so ..2.. => 1..2..
 * Using these observations, we get the final transitions of dp[i][j] = (dp[i - 1][j] + dp[i - 1][j - 1] if i == a or i == b),
 * or (j * dp[i - 1][j + 1]) + ((j - (i > a) - (i > b)) * dp[i - 1][j - 1]) 
 */

#include <bits/stdc++.h> 
using namespace std;

using ll = long long;

using vi = vector<int>;
#define pb push_back
#define rsz resize
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using pi = pair<int,int>;
#define f first
#define s second
#define mp make_pair

const int MOD = (int) 1e9 + 7;

ll dp[2005][2005];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, a, b; cin >> n >> a >> b;
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == a || i == b) {
                dp[i][j] = dp[i - 1][j] + dp[i - 1][j - 1];
            }
            else {
                dp[i][j] = ((j * dp[i - 1][j + 1]) % MOD) + (((j - (i > a) - (i > b)) * dp[i - 1][j - 1]) % MOD) % MOD;
            }
        }
    }
    cout << dp[n][1] << '\n';
}

