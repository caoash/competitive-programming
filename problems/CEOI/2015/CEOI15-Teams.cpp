#pragma GCC optimize ("Ofast")
#pragma GCC target ("avx2")

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

const int MX = 10005;
const int MOD = (int) (1e6 + 7);
const ll INF = (ll) 1e18;

ll dp[2][MX];

int main(){
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    ll ans = 0;
    vl a(n);
    vl pref(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        pref[i] = a[i];
        if (i) pref[i] = max(pref[i], pref[i - 1]);
    }
    for (int i = 1; i <= n; i++) dp[0][i] = 1;
    for (int i = 0; i < n; i++) {
        if (i) {
            for (int j = 1; j < n; j++) {
                dp[i & 1][j] = (dp[(i & 1) ^ 1][j] * j) % MOD;
                dp[i & 1][j] += dp[(i & 1) ^ 1][j + 1];
                while (dp[i & 1][j] > MOD) dp[i & 1][j] -= MOD;
            }
        }
        int pos = n - (i + 1);
        ans = (ans + (ll) (a[pos] - 1) * dp[i & 1][(pos == 0 ? 0 : pref[pos - 1])]) % MOD;
    }
    cout << (ans + 1) % MOD << '\n';
}

