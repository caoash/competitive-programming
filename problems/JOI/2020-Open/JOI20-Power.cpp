/*
 * Observe that you can only have one node be a parent of another. Let dp[v] = max profit you can get if no chosen node is a parent of another chosen node.
 *
 * Then, if node v has a generator, dp[v] = sum of dp[child_v] - 1, and if it doesn't, dp[v] = sum of dp[child_v].
 *
 * Finally, since you can have one node be the parent of another, ans = max(ans, dp[v], dp[child_v] + 1) over all v.
 */

#include <bits/stdc++.h> 
using namespace std;

using ll = long long;

using vi = vector<int>;
#define pb push_back
#define rsz resize
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using pi = pair<int,int>;
#define f first
#define s second
#define mp make_pair

const int MX = 200005;

vi adj[MX];
string s;
ll ans = 0;
ll dp[MX];

void dfs(int v, int p) {
    if (s[v] == '1') {
        ll best = 0;
        for (int to : adj[v]) {
            if (to != p) {
                dfs(to, v);
                dp[v] += dp[to];
                best = max(best, dp[to] + 1);
            }
        }
        ans = max(ans, best);
        dp[v]--;
        dp[v] = max(dp[v], 1LL);
    }
    else {
        for (int to : adj[v]) {
            if (to != p) {
                dfs(to, v);
                dp[v] += dp[to];
            }
        }
    }
    ans = max(ans, dp[v]);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        int u, v; cin >> u >> v;
        u--, v--;
        adj[u].pb(v), adj[v].pb(u);
    }
    cin >> s;    
    dfs(0, -1);
    cout << ans << '\n';
}

