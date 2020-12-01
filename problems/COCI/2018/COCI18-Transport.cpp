/*
 * Centroid decomposition. Then to find paths that go through some root, compute the cost to start at x and go to the root (if you can). 
 *
 * Store a running set as you DFS to determine whether you can start at x and go to the root, and put the results in an indexed set (pbds).
 *
 * Then, for each child subtree, first remove all the values in the pbds. Afterwards, for all the other values you can do a quick query using pbds.
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
 
const int MX = 100005;
const int MOD = (int) (1e9 + 7);
const ll INF = (ll) 1e18;

#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <class T> using Tree = tree<T, null_type, less<T>, 
    rb_tree_tag, tree_order_statistics_node_update>; 
#define ook order_of_key
#define fbo find_by_order 

int n;
ll a[MX];
bool blocked[MX];
vector<pair<ll, int>> adj[MX];
ll ans = 0;
 
Tree<pair<ll, int>> fin;
ll dist[MX];
ll mdist[MX];
int sz[MX];
 
void dfs(int v, int p) {
    if (p != -1 && mdist[v] >= 0) ++ans;
    dist[v] += a[v];
    for (pi to : adj[v]) {
        if (blocked[to.f]) continue;
        if (to.f != p) {
            dist[to.f] = dist[v] - to.s;
            mdist[to.f] = min(mdist[v], dist[to.f]);
            dfs(to.f, v);
        }
    }
}
 
multiset<ll> curr;

void dfs2(int v, int p) {
    curr.insert(dist[v]);
    for (pi to : adj[v]) {
        if (blocked[to.f]) continue;
        if (to.f != p) {
            dfs2(to.f, v);
        }
    }
    if (dist[v] == (*--curr.end())) {
        if (p != -1) fin.insert(mp(dist[v], v));        
    }
    curr.erase(curr.find(dist[v]));
}
 
vi order;
 
void dfs3(int v, int p) {
    for (pi to : adj[v]) {
        if (blocked[to.f]) continue;
        if (to.f != p) {
            dfs3(to.f, v);
        }
    }
    order.pb(v);
}
 
void solve(int root) {
    dfs3(root, -1);
    for (int x : order) mdist[x] = INF;
    mdist[root] = 0;
    dist[root] = 0;
    dfs(root, -1);
    dfs2(root, -1);
    vector<bool> ok(n);
    for (auto &x : fin) {
        ok[x.s] = true;
    }
    ans += sz(fin);
    order.clear();
    for (pi to : adj[root]) {
        if (blocked[to.f]) continue;
        dfs3(to.f, root);
        for (int x : order) {
            if (ok[x]) {
                fin.erase(mp(dist[x], x));     
            }
        }
        for (int x : order) {
            ll cdist = mdist[x];
            ans += sz(fin) - fin.order_of_key(mp(-cdist + a[root], INT_MIN));
        }
        for (int x : order) {
            if(ok[x]) fin.insert(mp(dist[x], x)); 
        }
        order.clear();
    }
    fin.clear();
}
 
void dfs4(int v, int p) {
    sz[v] = 1;
    for (pi to : adj[v]) {
        if (blocked[to.f]) continue;
        if (to.f != p) {
            dfs4(to.f, v);
            sz[v] += sz[to.f];
        }
    }
}
 
int find(int v, int p, int root) {
    for (pi to : adj[v]) {
        if (blocked[to.f]) continue;
        if (to.f != p) {
            if (sz[to.f] > sz[root] / 2) {
                return find(to.f, v, root);
            }
        }
    }
    return v;
}
 
void go(int root) {
    dfs4(root, -1);
    int cc = find(root, -1, root);
    solve(cc);
    blocked[cc] = true;
    for (pi to : adj[cc]) {
        if (!blocked[to.f]) {
            go(to.f);
        }
    }
}
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n - 1; i++) {
        int u, v, w; cin >> u >> v >> w;
        u--, v--;
        adj[u].pb(mp(v, w)), adj[v].pb(mp(u, w));
    }
    go(0);
    cout << ans << '\n';
} 
