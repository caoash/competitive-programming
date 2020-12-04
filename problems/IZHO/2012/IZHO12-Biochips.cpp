/*
 * Tree DP on preorder traversal.
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

const int MX = 200005;
const int MOD = (int) (1e9 + 7);
const ll INF = (ll) 1e18;

vi adj[MX];
int dp[MX][505];
int st[MX], sz[MX], val[MX], pos[MX];
int cnt = 0;

void dfs(int v, int p) {
    pos[cnt] = v;
    st[v] = cnt++;
    sz[v] = 1;
    for (int to : adj[v]) {
        if (to != p) {
            dfs(to, v); 
            sz[v] += sz[to];
        }
    }
}

int main(){
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m; cin >> n >> m;
    int root = -1;
    for (int i = 0; i < n; i++) {
        int p, x; cin >> p >> x;
        p--;
        val[i] = x;
        if (p != -1) {
            adj[p].pb(i);
        } else {
            root = i;
        }
    }
    memset(dp, -0x3f3f3f, sizeof(dp));
    dp[0][0] = 0;
    dfs(root, -1);
    for (int i = 0; i < cnt; i++) {
        for (int j = 0; j <= m; j++) {
            int cur = pos[i];
            int nxt = st[cur] + sz[cur];
            if (j < m) dp[nxt][j + 1] = max(dp[nxt][j + 1], dp[i][j] + val[cur]);
            dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);
        }
    }
    cout << dp[cnt][m] << '\n';
}

