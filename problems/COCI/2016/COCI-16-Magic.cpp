/*
 * Do rerooting DP since there can only be one non-1 node on a path.
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

const int MX = 1000005;
const int MOD = (int) (1e9 + 7);
const ll INF = (ll) 1e18;

struct fr{
    ll x, y;

    fr(ll X = 0, ll Y = 1){
        x = X, y = Y;
        ll g = __gcd(x, y);
        x /= g, y /= g;
    }

    friend fr operator+(fr a, fr b){
        return fr(a.x * b.y + b.x * a.y, a.y * b.y);
    }

    friend fr operator-(fr a, fr b){
        return fr(a.x * b.y - b.x * a.y, a.y * b.y);
    }

    friend fr operator*(fr a, fr b){
        return fr(a.x * b.x, a.y * b.y);
    }

    friend fr operator/(fr a, fr b){
        return fr(a.x * b.y, a.y * b.x);
    }

    friend bool operator<(fr a, fr b){
        return a.x * b.y < b.x * a.y;
    }
};

int dat[MX];
vi adj[MX];
ll dp[MX], dp2[MX];
int anc[MX];

void dfs(int v, int p) {
    if (dat[v] == 1) dp[v] = 1;
    for (int to : adj[v]) {
        if (to == p) continue;
        anc[to] = v;
        dfs(to, v);
        if (dp[to] + (dat[v] == 1) > dp[v]) {
            dp[v] = dp[to] + (dat[v] == 1);
        }
    }
    if (dat[v] > 1) dp[v] = 0;
}

int main(){
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        u--, v--;
        adj[u].pb(v), adj[v].pb(u);
    }
    memset(anc, -1, sizeof(anc));
    for (int i = 0; i < n; i++) {
        cin >> dat[i];
    }
    dfs(0, -1);
    queue<int> bfs;
    fr ans = fr(INF);
    bfs.push(0);
    while (!bfs.empty()) {
        int curr = bfs.front();
        bfs.pop();
        for (int to : adj[curr]) {
            if (to != anc[curr]) bfs.push(to);
        }
        if (anc[curr] != -1) {
            if (dat[anc[curr]] == 1) {
                dp2[curr] = dp2[anc[curr]] + 1;
                for (int to : adj[anc[curr]]) {
                    if (to != curr && to != anc[anc[curr]]) {
                        dp2[curr] = max(dp2[curr], dp[to] + 1);
                    }
                }
            } else {
                dp2[curr] = 0;
            }
        }
        ll best = dp2[curr], sbest = 0;
        for (int to : adj[curr]) {
            if (to != anc[curr]) {
                if (dp[to] > best) {
                    sbest = best, best = dp[to];
                } else if (dp[to] > sbest) {
                    sbest = dp[to];
                }
            }
        }
        fr ret = {dat[curr], best + sbest + 1};
        if (ret < ans) ans = ret;
        ret = {dat[curr]};
        if (ret < ans) ans = ret;
    }
    cout << ans.x << "/" << ans.y << '\n';
}

