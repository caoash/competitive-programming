/*
 * Let dp[v][x] = maximum pairs you can get in subtree of v with x unpaired white nodes.
 *
 * Then you can do combining subtrees dp to compute the answer, which runs in O(N^2).
 */

#include <bits/stdc++.h> 
using namespace std;

using ll = long long;

using vi = vector<int>;
using vl = vector<ll>;
using vpl = vector<pair<ll, ll>>;
#define pb push_back
#define rsz resize
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using pi = pair<int,int>;
#define f first
#define s second
#define mp make_pair

const int MX = 5005;
const int MOD = (int) (1e9 + 7);
const ll INF = (ll) 1e18;

int n;
vpl dp[MX];
vi adj[MX];

vpl comb(vpl &a, vpl &b) {
    vpl c(sz(a) + sz(b) - 1);
    for (int i = 0; i < sz(a); i++) {
        for (int j = 0; j < sz(b); j++) {
            ll curr = a[i].f + b[j].f + (i * j);
            if (curr > c[i + j].f) {
                c[i + j].f = curr;
                c[i + j].s = a[i].s + b[j].f;
            }
        }
    }
    return c;
}

ll ans = 0;

void fin(vpl &c) {
    if (sz(c) <= 1) c.pb(mp(0, 0));
    else {
        for (int i = 0; i < sz(c); i++) {
            c[1].f = max(c[1].f, i + c[i].s);
        }
    }
}

bool vis[MX];

void dfs(int v, int p) {
    vis[v] = true;
    dp[v] = {mp(0, 0)};
    for (int to : adj[v]) {
        if (to != p) {
            dfs(to, v);
            dp[v] = comb(dp[v], dp[to]);
        }
    }
    fin(dp[v]);
}

int main(){
    ifstream cin("tricolor.in");
    ofstream cout("tricolor.out");
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T; cin >> T;
    while (T--) {
        ans = 0;
        cin >> n;
        for (int i = 0; i < n; i++) adj[i].clear();
        for (int i = 0; i < n; i++) dp[i].clear();
        memset(vis, false, sizeof(vis));
        for (int i = 0; i < n - 1; i++) {
            int u, v; cin >> u >> v;
            u--, v--;
            adj[u].pb(v), adj[v].pb(u);
        }
        for (int i = 0; i < n; i++) {
            if(!vis[i]) {
                dfs(i, -1);
            }
        }
        ans = (max_element(all(dp[0])) -> f);
        cout << ans << '\n';
    }
}

