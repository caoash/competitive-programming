/*
 * Since you want to cut some subtrees, we can change to problem on array by using preorder traversal. Then it becomes pretty standard DP problem, except you need to constant factor
 * optimize a lot because infoarena has a very low time limit.
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

const int MX = 3005;
const int MOD = (int) 31333; 
const ll INF = (ll) 1e18;
 
int n, p; 
int a[MX];
vi adj[MX];
int dp[MX][3505];
int sz[MX];
int rev[MX];
int pows[MX];
 
int cnt = 0;
 
void dfs_init(int v, int p) {
    sz[v] = 1;
    rev[cnt] = v;
    cnt++;
    for (int to : adj[v]) {
        if (to != p) {
            dfs_init(to, v);
            sz[v] += sz[to];
        }
    }
}
 
int main(){
    /*
    ifstream cin("radare.in");
    ofstream cout("radare.out");
    */
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> p;
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        u--, v--;
        adj[u].pb(v), adj[v].pb(u);
    }
    for (int i = 0; i < n; i++) cin >> a[i];
    dfs_init(0, -1);
    dp[0][0] = 1;
    pows[0] = 1;
    for (int i = 1; i <= n; i++) {
        pows[i] = (pows[i - 1] << 1);
        if (pows[i] >= MOD) pows[i] -= MOD;
    }
    for (int i = 0; i < n; i++) {
        int to = rev[i];
        for (int j = 0; j <= p; j++) {
            if (!dp[i][j]) continue;
            if (i != n && j + a[to] <= p) {
                dp[i + 1][j + a[to]] += dp[i][j];
                if (dp[i + 1][j + a[to]] >= MOD) dp[i + 1][j + a[to]] -= MOD;
            }
            if (i != 0) {
                dp[i + sz[to]][j] += (dp[i][j] * pows[sz[to] - 1]);
                dp[i + sz[to]][j] %= MOD;
            }
        }
    }
    cout << dp[n][p] << '\n';
}
