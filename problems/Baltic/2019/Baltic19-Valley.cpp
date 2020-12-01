/*
 * Rewrite depth[v] + depth[v] - 2 * lca[depth(u, v)] by fixing the lca. For some lca, i, we can set it to min(depth[v] - 2 * depth[i]) where v is a shop, and then for some u find the minimum value of an lca using binary lifting. If you root it at the exit, you can easily break the problem into if you escape or not, and if you don't escape, you just need to answer the query in a subtree which is easier.
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

const int MX = 100005;
const ll INF = (ll) 1e18;

vector<pi> adj[MX]; ll dep[MX], dp[MX]; int tin[MX], tout[MX]; bool village[MX];

template<int SZ> struct LCA{
    int depth[SZ]; int p[SZ][33]; vector<int> adj[SZ]; ll p_min[SZ][33];
    void addEdge(int u, int v){
      adj[u].push_back(v); adj[v].push_back(u);
    }
    void dfs(int v, int par){
        for(int to : adj[v]){
          if(to != par){
            p[to][0] = v; depth[to] = depth[v] + 1;
            dfs(to, v);
          }
        }
    }
    void precomp(int root, ll dp[MX]) {
        for (int i = 0; i < SZ; i++) {
            for (int j = 0; j < 32; j++) {
                p[i][j] = -1;
                p_min[i][j] = INT_MAX;
            }
            p_min[i][0] = dp[i];
        }
        p[root][0] = root;
        dfs(root, -1);
        for (int j = 1; j < 32; j++) {
            for (int i = 0; i < SZ; i++) {
                if (p[i][j - 1] == -1) {
                    p[i][j] = -1;
                    p_min[i][j] = INT_MAX;
                } else {
                    p[i][j] = p[p[i][j - 1]][j - 1];
                    p_min[i][j] = min(p_min[i][j - 1], p_min[p[i][j - 1]][j - 1]);
                }
            }
        }
    }
    int gdep(int v) {
        return depth[v];
    }
    int query(int a, int b) {
        if (depth[a] > depth[b]) {
            swap(a, b);
        }
        int lift = depth[b] - depth[a];
        for (int j = 31; j >= 0; j--) {
            if (lift & (1 << j)) {
                b = p[b][j];
            }
        }
        for (int j = 31; j >= 0; j--) {
            if (p[a][j] != p[b][j]) {
                a = p[a][j];
                b = p[b][j];
            }
        }
        return (a == b) ? a : p[a][0];
    }
    ll query2(int a, int b) {
        int curr = a;
        ll ans = INF;
        for(int i = 31; i >= 0; i--){
            if(b & (1 << i)) {
                ans = min(p_min[curr][i], ans);
                curr = p[curr][i];
            }
        }
        assert(curr != -1);
        return ans;
    }
};

LCA<MX> anc; 

int cnt = 0;

void dfs(int v, int p) {
    tin[v] = cnt++;
    for (pi to : adj[v]) {
        if (to.f != p) {
            dep[to.f] = dep[v] + to.s;
            dfs(to.f, v);
        }
    }
    tout[v] = cnt++;
}

void dfs2(int v, int p) {
    if (village[v]) {
        dp[v] = dep[v];
    }
    for (pi to : adj[v]) {
        if (to.f != p) {
            dfs2(to.f, v);
            dp[v] = min(dp[v], dp[to.f]);
        }
    }
} 

bool is_anc(int u, int v) {
    if (u == v) return true;
    else if((tin[u] < tin[v] && tout[u] > tout[v])) return true;
	return false;
}

vector<pi> ed;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, s, q, e; cin >> n >> s >> q >> e;
    e--;
    for (int i = 0; i < n - 1; i++) {
        int u, v, w; cin >> u >> v >> w;
        u--, v--;
        adj[u].pb(mp(v, w)), adj[v].pb(mp(u, w));
        anc.addEdge(u, v);
        ed.pb(mp(u, v));
    }
    for (int i = 0; i < s; i++) {
        int x; cin >> x; 
        x--;
        village[x] = true;
    }
    dfs(e, -1);
    for (int i = 0; i < n; i++) dp[i] = INF;
    dfs2(e, -1);
    for (int i = 0; i < n; i++) if(dp[i] != INF) dp[i] -= 2 * dep[i];
    anc.precomp(e, dp);
    for (int i = 0; i < q; i++) {
        int ind, r; cin >> ind >> r;
        ind--, r--;
        pi curr = ed[ind];
        if (dep[curr.s] < dep[curr.f]) swap(curr.f, curr.s);
        if (is_anc(curr.s, r)) {
            int dist = anc.gdep(r) - anc.gdep(curr.f);
            ll ret = anc.query2(r, dist);
            if (ret == INF) {
                cout << "oo" << '\n';
            }
            else {
                ret += dep[r];
                cout << ret << '\n';
            }
        }
        else {
            cout << "escaped" << '\n';
        }
    }
}

