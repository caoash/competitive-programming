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

const int MX = 100005;
const int MOD = (int) (1e9 + 7);
const ll INF = (ll) 1e18;

vi adj[MX];
int deg[MX];
ll dp[MX];
ll a[MX];
int root = -1;

void dfs(int v, int p) {
    ll sum = 0;
    ll mx = 0;
    if (deg[v] == 1) dp[v] = a[v];
    else {
        int child = 0;
        for (int to : adj[v]) {
            if (to != p) {
                dfs(to, v);
                ++child;
                sum += dp[to];
                mx = max(mx, dp[to]);
            }
        }
        if (v != root && child > 1) {
            if (2 * a[v] >= sum && sum >= a[v] && sum - mx >= sum - a[v]) {
                dp[v] = 2 * a[v] - sum;
            } else {
                dp[v] = -1;
            }
        } else if (child == 1) {
            bool bad = false;
            for (int to : adj[v]) {
                if (to != p) {
                    dp[v] = dp[to];
                    if (dp[to] != a[v]) bad = true;
                }
            }
            if (bad) dp[v] = -1;
            if (v == root) dp[v] = -1;
        } else {
            for (int to : adj[v]) {
                if (to != p) mx = max(mx, dp[to]);
            }
            if (sum % 2) dp[v] = -1;
            else {
                if (2 * mx > sum || sum < 2 * a[v] || sum - mx < sum - a[v]) dp[v] = -1;
                else {
                    if (sum / 2 != a[v]) dp[v] = -1;
                    else dp[v] = 2 * a[v] - sum;
                }
            }
        }
        for (int to : adj[v]) {
            if (to != p) {
                if (dp[to] == -1) dp[v] = -1;
            }
        }
    }
    // dbg(v, dp[v]);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        u--, v--;
        // cout << u << " " << v << '\n';
        adj[u].pb(v), adj[v].pb(u);
        deg[u]++, deg[v]++;
    }
    for (int i = 0; i < n; i++) {
        if (deg[i] > 1) root = i;
    }
    if (n == 2) {
        if (a[0] == a[1]) cout << "YES\n";
        else cout << "NO\n";
    } else {
        assert(root != -1);
        dfs(root, -1);
        if (dp[root] != -1) cout << "YES\n";
        else cout << "NO\n";
    }
}

