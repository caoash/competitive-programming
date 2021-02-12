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

int n;
ll dp[1005][1005][2];
ll a[1005];

ll solve(int l, int r, int t) {
    if (dp[l][r][t] != -INF) {
        return dp[l][r][t];
    } else if (l > r) {
        return -INF;   
    } else if (l == r) {
        dp[l][r][t] = (t ? -1 : 1) * a[l];   
        return dp[l][r][t];
    } else {
        if (t == 1) {
            if (a[l] >= a[r]) dp[l][r][t] = solve(l + 1, r, t ^ 1) - a[l];
            else dp[l][r][t] = solve(l, r - 1, t ^ 1) - a[r];
            return dp[l][r][t];
        } else {
            dp[l][r][t] = max(solve(l + 1, r, t ^ 1) + a[l], solve(l, r - 1, t ^ 1) + a[r]); 
            return dp[l][r][t];
        }
    }
}

int main(){
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tc = 1;
    while (cin >> n) {
        if (n == 0) break;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) dp[i][j][0] = -INF, dp[i][j][1] = -INF;
        printf("In game %d, the greedy strategy might lose by as many as %lld points.\n", tc++, solve(0, n - 1, 0));
    }
}

