#include <bits/stdc++.h> 
using namespace std;

typedef long long LL;

#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)

#define F first
#define S second

int n;
int dp[405][405];
int a[405];

int Solve(int l, int r) {
    if (dp[l][r] != -1) return dp[l][r];
    if (r < l) return 1;
    else if (l == r) return 1;
    else {
        int sum = 0, sum2 = 0;
        int p2 = r + 1;
        F0R(k, l, r + 1) {
            sum += a[k];
            while (sum2 < sum && p2 >= k) --p2, sum2 += a[p2];
            if (p2 < k) break;
            if (sum == sum2 && Solve(l, k) && Solve(p2, r)) {
                if (Solve(k + 1, p2 - 1)) return dp[l][r] = 1;
            }
        }
        return dp[l][r] = 0;
    }
}

int main(){
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    memset(dp, -1, sizeof(dp));
    int ans = 0;
    FOR(i, n) {
        int sum = 0;
        F0R(j, i, n) {
            sum += a[j];
            if (Solve(i, j)) ans = max(ans, sum);
        }
    }
    cout << ans << '\n';
}

