/*
 * Reduce the problem to pairing LCAs with distance formula, then realize if you choose the centroid you can always pair nodes using the root as LCA.
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

const int MX = 200005;
const int MOD = (int) (1e9 + 7);
const ll INF = (ll) 1e18;

int n, m;
int sz[MX];
vector<pi> adj[MX];
int dist[MX];

void dfs(int v, int p) {
    for (pi to : adj[v]) {
        if (to.f != p) {
            dfs(to.f, v);
            sz[v] += sz[to.f];
        }
    }
}

int find(int v, int p) {
    for (pi to : adj[v]) {
        if (to.f != p) {
            if (sz[to.f] >= n / 2) {
                return find(to.f, v);
            }
        }
    }
    return v;
}

void dfs_dist(int v, int p) {
    for (pi to : adj[v]) {
        if (to.f != p) {
            dist[to.f] = dist[v] + to.s;
            dfs_dist(to.f, v);
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    vi a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
        sz[a[i]]++;
    }
    for (int i = 0; i < m - 1; i++) {
        int u, v, w; cin >> u >> v >> w;
        u--, v--;
        adj[u].pb(mp(v, w));
        adj[v].pb(mp(u, w));
    }
    dfs(0, -1);
    int cent = find(0, -1);
    dfs_dist(cent, -1);
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ans += dist[a[i]];
    }
    cout << ans << '\n';
}

