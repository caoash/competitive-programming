#include <bits/stdc++.h> 
using namespace std;
 
typedef long long ll;
 
#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)
 
#define F first
#define S second

const int MX = 10005;

vector<pair<int, int>> adj[MX];
int dep[MX];

template < int SZ > struct LCA {
  int depth[SZ];
  int p[SZ][33];
  vector < int > adj[SZ];
  void addEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  void dfs(int v, int par) {
    for (int to: adj[v]) {
      if (to != par) {
        p[to][0] = v;
        depth[to] = depth[v] + 1;
        dfs(to, v);
      }
    }
  }
  void precomp(int root) {
    for (int i = 0; i < SZ; i++) {
      for (int j = 0; j < 32; j++) {
        p[i][j] = -1;
      }
    }
    p[root][0] = 0;
    dfs(root, -1);
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

LCA<MX> lca;

void dfs(int v, int p) {
    for (auto to : adj[v]) {
        if (to.F != p) {
            dep[to.F] = dep[v] + to.S;
            dfs(to.F, v);
        }
    }
}

pair<int, int> diam(int v, int p, int d) {
    pair<int, int> res = make_pair(v, d);
    for (auto to : adj[v]) {
        if (to.F != p) {
            pair<int, int> go = diam(to.F, v, d + to.S);
            if (go.S > res.S) res = go;
        }
    }
    return res;
}

int dist(int u, int v) {
    return dep[v] + dep[u] - 2 * dep[lca.query(u, v)];
}
 
int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);    
    int n; cin >> n;
    FOR(i, n - 1) {
        int p, w; cin >> p >> w;
        p--;
        adj[p].push_back(make_pair(i + 1, w));
        adj[i + 1].push_back(make_pair(p, w));
        lca.addEdge(p, i + 1);
    }
    dfs(0, -1);
    lca.precomp(0);
    pair<int, int> best = diam(0, -1, 0);
    pair<int, int> fin = make_pair(-1, -1);
    fin.F = best.F;
    best = diam(fin.F, -1, 0);
    fin.S = best.F;
    FOR(i, n) {
        cout << max(dist(i, fin.F), dist(i, fin.S)) << '\n';
    }
}

