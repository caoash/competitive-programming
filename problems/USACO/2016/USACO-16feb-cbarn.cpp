/*
 * If the best transition is nondecreasing, you can compute the DP in nlogn.
 *
 * Let's make the circular array linear by fixing the position of the first door.
 *
 * Then, we can solve it in NKlogN with divide and conquer DP since the optimal door
 * is monotonic.
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

const int MX = 1005;
const int MOD = (int) (1e9 + 7);
const ll INF = (ll) 1e18;

int N, K;
ll cost[2 * MX][2 * MX];
ll dp[MX][8];

ll C(int l, int r, int off) {
    return cost[l + off][r + off];
}

void go(int l, int r, int opl, int opr, int k, int off) {
    if (l > r) return;
    int mid = (l + r) / 2;
    dp[mid][k] = INF;
    int opt = -1;
    for (int j = max(opl, mid + 1); j <= opr; j++) {
        ll ccost = (j == N - 1 ? 0 : dp[j + 1][k - 1]) + C(mid, j, off);
        if (ccost < dp[mid][k]) {
            dp[mid][k] = ccost;
            opt = j;
        }
    }
    go(l, mid - 1, opl, opt, k, off);
    go(mid + 1, r, opt, opr, k, off);
}

ll solve(int off) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < K; j++) {
            dp[i][j] = INF;
        }
    }
    for (int i = 0; i < N; i++) dp[i][0] = C(i, N - 1, off);
    for (int i = 1; i < K; i++) {
        go(0, N - 1, 0, N - 1, i, off);
    }
    return dp[0][K - 1];
}

int main(){
    freopen("cbarn.in", "r", stdin);
    freopen("cbarn.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> N >> K;
    vi a(2 * N);
    for (int i = 0; i < N; i++) cin >> a[i];
    for (int i = N; i < 2 * N; i++) a[i] = a[i - N];
    for (int i = 0; i < 2 * N; i++) {
        cost[i][i] = 0;
        for (int j = i + 1; j < 2 * N; j++) {
            cost[i][j] = cost[i][j - 1] + (j - i) * a[j];
        }
    }
    ll ans = INF;
    for (int off = 0; off < N; off++) {
        ans = min(ans, solve(off));
    }
    cout << ans << '\n';
}

