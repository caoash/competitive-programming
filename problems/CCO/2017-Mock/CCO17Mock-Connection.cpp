/*
 * Use DSU to maintain a tree. If you create a cycle, then update a path with the day you created it (the day that the edge became not a bridge).
 *
 * Then, you can answer queries with a max query.
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

const int MX = 150005;
const int MOD = (int) (1e9 + 7);
const ll INF = (ll) 1e18;

template < int SZ > struct DSU {
  int p[SZ], sz[SZ];
  void init() {
    for (int i = 0; i < SZ; i++) {
      p[i] = i;
      sz[i] = 1;
    }
  }
  int find(int x) {
    return p[x] = (p[x] == x ? x : find(p[x]));
  }
  void merge(int u, int v) {
    int a = find(u);
    int b = find(v);
    if (a != b) {
      if (sz[a] < sz[b]) {
        swap(a, b);
      }
      p[b] = a;
      sz[a] += sz[b];
    }
  }
};

template < int SZ > struct LCA {
  int depth[SZ];
  int p[SZ][33];
  bool vis[SZ];
  vector < int > adj[SZ];
  void addEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  void dfs(int v, int par) {
    vis[v] = true;
    for (int to: adj[v]) {
      if (to != par) {
        p[to][0] = v;
        depth[to] = depth[v] + 1;
        dfs(to, v);
      }
    }
  }
  void precomp() {
    for (int i = 0; i < SZ; i++) {
      for (int j = 0; j < 32; j++) {
        p[i][j] = -1;
      }
    }
    for (int i = 0; i < SZ; i++) {
        if (!vis[i]) {
            p[i][0] = 0;
            dfs(i, -1);
        }
    }
    for (int j = 1; j < 32; j++) {
      for (int i = 0; i < SZ; i++) {
        if (p[i][j - 1] == -1) {
          p[i][j] = -1;
        } else {
          p[i][j] = p[p[i][j - 1]][j - 1];
        }
      }
    }
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
};

template <int SZ> struct BLIFT {
  int depth[SZ];
  int p[SZ][33];
  int pmx[SZ][33];
  bool vis[SZ];
  vector<pi> adj[SZ];
  void addEdge(int u, int v, int w) {
    adj[u].push_back(mp(v, w));
    adj[v].push_back(mp(u, w));
  }
  void dfs(int v, int par) {
    vis[v] = true;
    for (pi to : adj[v]) {
      if (to.f != par) {
        p[to.f][0] = v;
        pmx[to.f][0] = to.s;
        depth[to.f] = depth[v] + 1;
        dfs(to.f, v);
      }
    }
  }
  void precomp() {
    for (int i = 0; i < SZ; i++) {
      for (int j = 0; j < 32; j++) {
        p[i][j] = -1;
        pmx[i][j] = -1;
      }
    }
    for (int i = 0; i < SZ; i++) {
        if (!vis[i]) {
            p[i][0] = 0;
            pmx[i][0] = 0;
            dfs(i, -1);
        }
    }
    for (int j = 1; j < 32; j++) {
      for (int i = 0; i < SZ; i++) {
        if (p[i][j - 1] == -1) {
          p[i][j] = -1;
          pmx[i][j] = -1;
        } else {
          p[i][j] = p[p[i][j - 1]][j - 1];
          pmx[i][j] = max(pmx[i][j - 1], pmx[p[i][j - 1]][j - 1]);
        }
      }
    }
  }
  int query(int a, int b) {
    if (depth[a] > depth[b]) {
      swap(a, b);
    }
    int lift = depth[b] - depth[a];
    int ans = 0;
    for (int j = 31; j >= 0; j--) {
      if (lift & (1 << j)) {
        ans = max(ans, pmx[b][j]);
        b = p[b][j];
      }
    }
    for (int j = 31; j >= 0; j--) {
      if (p[a][j] != p[b][j]) {
        ans = max(ans, pmx[a][j]);
        ans = max(ans, pmx[b][j]);
        a = p[a][j];
        b = p[b][j];
      }
    }
    return (a == b) ? ans : max(ans, max(pmx[a][0], pmx[b][0]));
  }
};

LCA<MX> anc;
DSU<MX> dsu, idsu;
vi upds[MX][2];
set<int> vals[MX];
vector<pi> ed;
vi adj[MX];
int w[MX];
bool vis[MX];
BLIFT<MX> qr;

void mrg(set<int> &v1, set<int> &v2) {
    if (sz(v1) < sz(v2)) swap(v1, v2);
    for (auto &x : v2) v1.insert(x);
    v2.clear();
}

void pull(int v, int p) {
    vis[v] = true;
    for (auto x : upds[v][0]) vals[v].insert(x); 
    for (int to : adj[v]) {
        if (to != p) {
            pull(to, v);
            if (!vals[to].empty()) w[to] = min(w[to], *(vals[to].begin()));
            mrg(vals[v], vals[to]);
        }
    }
    for (auto x : upds[v][1]) {
        assert(vals[v].count(x));
        vals[v].erase(x);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m, q; cin >> n >> m >> q;
    dsu.init();
    idsu.init();
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        if (u != v) {
            if (idsu.find(u) != idsu.find(v)) {
                anc.addEdge(u, v);
                idsu.merge(u, v);
                adj[u].pb(v), adj[v].pb(u);
            }
        }
        ed.pb(mp(u, v));
    }
    anc.precomp();
    for (int i = 0; i < sz(ed); i++) {
        auto x = ed[i];
        if (x.f == x.s) continue;
        if (dsu.find(x.f) != dsu.find(x.s)) {
            dsu.merge(x.f, x.s);
        } else {
            upds[x.f][0].pb(i);
            upds[x.s][0].pb(i);
            int to = anc.query(x.f, x.s);
            assert(to != -1);
            upds[to][1].pb(i);
        }
    }
    for (int i = 0; i <= n; i++) w[i] = INT_MAX;
    for (int i = 0; i <= n; i++) {
        if (!vis[i]) pull(i, -1);
    }
    for (int i = 0; i <= n; i++) {
        int u = i, v = anc.p[i][0], cw = w[i];
        if (v != -1) qr.addEdge(u, v, cw);
    }
    qr.precomp();
    for (int i = 0; i < q; i++) {
        int qu, qv; cin >> qu >> qv;
        if (dsu.find(qu) != dsu.find(qv)) {
            cout << -1 << '\n';
            continue;
        }
        if (qu == qv) {
            cout << 0 << '\n';
            continue;
        }
        int ans = qr.query(qu, qv);
        if (ans == INT_MAX) {
            cout << -1 << '\n';
        } else {
            cout << ans << '\n';
        }
    }
} 

