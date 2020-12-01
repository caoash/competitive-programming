#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx,avx2,sse,sse2")

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

const int MX = 200005;
const int MOD = (int) (1e9 + 7);
const ll INF = (ll) 1e18;

ll dp[3005][3005];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, k, x, v; cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        cin >> x;
        ll sum = 0;
        for (int j = 0; j <= k; ++j) dp[i][j] = max(dp[i][j], dp[i - 1][j]); 
        for (int y = 0; y < x; ++y) {
            cin >> v;
            sum += v;
            for (int j = y + 1; j <= k; ++j) {
                dp[i][j] = max(dp[i][j], dp[i - 1][j - (y + 1)] + sum);
            }
        }
    }
    cout << dp[n][k] << '\n';
}

