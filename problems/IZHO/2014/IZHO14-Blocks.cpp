/*
 * Let dp[i][j] = min sum for j groups if i is the end of the rightmost group.
 *
 * Let lft[i] = rightmost element > a[i] to the left of i
 *
 * Then there's two cases:
 * - i is largest in the group
 *   - if this is true, then you can transition from any dp value with j - 1 from [lft[i], i - 1] because you can create a group with anything that's not greater
 * - i is not the largest in the group
 *   - then dp[i][j] will equal dp[lft[i]][j], since you can just add i to the group of lft[i]
 */

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

const int MX = 100001;
const int MOD = (int) (1e9 + 7);
const int INF = 987654321;

int dp[MX][101];
int n;

struct Node {
    int val;
};

int t[4 * MX];

void upd(int p, int v) { 
  for (t[p += (n + 1)] = v; p > 1; p >>= 1) t[p >> 1] = min(t[p], t[p^1]);
}

int query(int l, int r) {
  int res = INF;
  for (l += (n + 1), r += (n + 1); l < r; l >>= 1, r >>= 1) {
    if (l&1) res = min(res, t[l++]);
    if (r&1) res = min(res, t[--r]);
  }
  return res;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int k; cin >> n >> k;
    vi a(n + 1), lft(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    stack<pi> stk;
    for (int i = 1; i <= n; i++) {
        while (!stk.empty() && stk.top().f <= a[i]) {
            stk.pop();
        }
        lft[i] = (stk.empty() ? 0 : stk.top().s);
        stk.push(mp(a[i], i));
    }
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= k; j++) {
            dp[i][j] = INF;
        }
    }
    dp[0][0] = 0;
    for (int j = 0; j <= k; j++) {
        for (int i = 1; i <= n; i++) {
            if (lft[i] != 0) dp[i][j] = min(dp[i][j], dp[lft[i]][j]);
            if (j) {
                dp[i][j] = min(dp[i][j], query(lft[i], i) + a[i]);
            }
        }
        for (int i = 0; i <= n; i++) {
            upd(i, dp[i][j]);
        }
    }
    cout << dp[n][k] << '\n';
}

