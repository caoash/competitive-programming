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

const int MX = 105;
const int MOD = (int) (1e9 + 7);
const ll INF = (ll) 1e18;

int cost[MX][MX];
int dp[MX][MX];
int fr[MX][MX];

int main(){
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int F, V; cin >> F >> V;
    memset(dp, -0x3f3f3f, sizeof(dp));
    dp[0][0] = 0;
    for (int i = 0; i < F; i++) {
        for (int j = 0; j < V; j++) {
            cin >> cost[i][j];
        }
    }
    for (int i = 1; i <= V; i++) dp[0][i] = dp[0][i - 1];
    for (int i = 1; i <= F; i++) {
        for (int j = 1; j <= V; j++) {
            int a = dp[i][j - 1], b = dp[i - 1][j - 1] + cost[i - 1][j - 1];
            if (a > b) dp[i][j] = a, fr[i][j] = 1;
            else dp[i][j] = b, fr[i][j] = -1;
        }
    }
    cout << dp[F][V] << '\n';
    pi cur = mp(F, V);
    vi ret;
    while (cur.f != 0) {
        int bef = fr[cur.f][cur.s];
        --cur.s;
        if (bef < 0) {
            ret.pb(cur.s);
            --cur.f;
        }
    }
    reverse(all(ret));
    for (auto x : ret) {
        cout << x + 1 << " ";
    }
}

