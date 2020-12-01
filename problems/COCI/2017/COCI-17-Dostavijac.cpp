/*
 * dp[node][time][return to subtree]
 *
 * then to compute it, do knapsack on tree
 *
 * you can do it a lot of ways but one is
 *
 * dp_pre[up to child i][time][return to subtree]
 *
 * then set dp[node][time][return to subtree] to dp[last child][time][return to subtree]
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

const int MX = 505;
const int MOD = (int) (1e9 + 7);
const ll INF = (ll) 1e18;

int n, m;
vi adj[MX];
int a[MX];
int dp[MX][MX][2];

void dfs(int v, int p) {
    vi child;
    for (int to : adj[v]) {
        if (to != p) {
            dfs(to, v);
            child.pb(to);
        }
    }
    int dp_pre[sz(child) + 1][m + 1][2];
    memset(dp_pre, -0x3f3f3f, sizeof(dp_pre));
    dp_pre[0][0][0] = 0;
    for (int i = 1; i <= sz(child); i++) {
        int to = child[i - 1];
        for (int j = 0; j <= m; j++) {
            for (int cj = 0; cj <= j; cj++) {
                if (j - cj - 2 >= 0) {
                    dp_pre[i][j][0] = max(dp_pre[i][j][0], dp_pre[i - 1][j - cj - 2][0] + dp[to][cj][0]);
                    dp_pre[i][j][1] = max(dp_pre[i][j][1], dp_pre[i - 1][j - cj - 2][1] + dp[to][cj][0]);
                }
                if (j - cj - 1 >= 0) {
                    dp_pre[i][j][1] = max(dp_pre[i][j][1], dp_pre[i - 1][j - cj - 1][0] + dp[to][cj][0]);
                    dp_pre[i][j][1] = max(dp_pre[i][j][1], dp_pre[i - 1][j - cj - 1][0] + dp[to][cj][1]);
                }
            }
            dp_pre[i][j][0] = max(dp_pre[i][j][0], dp_pre[i - 1][j][0]);
            dp_pre[i][j][1] = max(dp_pre[i][j][1], dp_pre[i - 1][j][1]);
        }
    }
    for (int i = 0; i <= m; i++) {
        dp[v][i][0] = dp_pre[sz(child)][i][0];
        dp[v][i][1] = dp_pre[sz(child)][i][1];
    }
    for (int i = m - 1; i >= 0; i--) {
        dp[v][i + 1][0] = max(dp[v][i + 1][0], dp[v][i][0] + a[v]);
        dp[v][i + 1][1] = max(dp[v][i + 1][1], dp[v][i][1] + a[v]);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        u--, v--;
        adj[u].pb(v), adj[v].pb(u);
    }
    dfs(0, -1);
    cout << max(dp[0][m][0], dp[0][m][1]) << '\n';
}

