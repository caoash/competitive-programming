#include <bits/stdc++.h> 
using namespace std;

typedef long long ll;

#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)

#define F first
#define S second

const int MX = 1005;

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
  void precomp() {
    for (int i = 0; i < SZ; i++) {
      for (int j = 0; j < 32; j++) {
        p[i][j] = -1;
      }
    }
    p[0][0] = 0;
    dfs(0, -1);
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
  int dist(int a, int b) {
    int ret = depth[a] + depth[b];
    int anc = query(a, b);
    if (anc != -1) ret -= 2 * depth[anc];
    return ret;
  }
  int gp(int u) {
    return p[u][0];
  }
};

struct Edge {
    int u, v, cost;
};

int n, m;

LCA<MX> lca;
vector<Edge> roads;
vector<int> rancs[MX];
vector<int> adj[MX];
bool block[MX];
int dp[MX][(1 << 10)];

void dfs(int v) {
    for (auto to : adj[v]) {
        if (to != lca.gp(v)) dfs(to);
    }
    FOR(i, n) block[i] = false;
    vector<pair<int, int>> todo(m + 1);
    vector<int> costs(m + 1);
    vector<pair<int, int>> bad(m + 1);
    FOR(i, rancs[v].size()) {
        int ind = rancs[v][i]; 
        auto ed = roads[ind];
        costs[i] = ed.cost;
        int a = ed.u, b = ed.v;
        int anc = lca.query(a, b);
        assert(anc == v);
        while (a != anc) {
            block[a] = true; 
            if (lca.gp(a) != anc) {
                a = lca.gp(a);
            } else {
                break;
            }
        }
        while (b != anc) {
            block[b] = true;
            if (lca.gp(b) != anc) {
                b = lca.gp(b);
            } else {
                break;
            }
        }
        bad[i] = {a, b};
        FOR(j, n) {
            if (block[j] || j == v) {
                int nmask = 0;
                FOR(k, adj[j].size()) {
                    if (adj[j][k] != lca.gp(v)) {
                        if (block[adj[j][k]]) nmask |= (1 << k);
                    }
                }
                if (j != v) {
                    costs[i] += dp[j][nmask];
                } else todo[i] = make_pair(j, nmask);
            }
        }
        FOR(j, n) block[j] = false;
    }
    FORD(mask, (1 << adj[v].size())) {
        int best = 0;
        FOR(i, rancs[v].size()) {
            bool no = false;
            FOR(k, adj[v].size()) {
                if ((mask & (1 << k)) && (adj[v][k] == bad[i].F || adj[v][k] == bad[i].S)) {
                    no = true;
                }
            }
            if (no) {
                continue;
            }
            int cost = costs[i] + dp[todo[i].F][todo[i].S | mask];
            best = max(best, cost);
        }
        int cost = 0;
        FOR(j, adj[v].size()) {
            int to = adj[v][j];
            if (to != lca.gp(v) && !(mask & (1 << j))) {
                cost += dp[to][0];
            }
        }
        best = max(best, cost);
        dp[v][mask] = best;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    vector<Edge> all;
    int tot = 0;
    FOR(i, m) {
        int u, v, t; cin >> u >> v >> t;
        u--, v--;
        tot += t;
        if (t == 0) {
            lca.addEdge(u, v);
            adj[u].push_back(v), adj[v].push_back(u);
        } else {
            all.push_back({u, v, t});
        }
    }
    lca.precomp();
    FOR(i, all.size()) {
        auto x = all[i];
        if (lca.dist(x.u, x.v) % 2) continue;
        roads.push_back(x);
        rancs[lca.query(x.u, x.v)].push_back(roads.size() - 1);
    }
    dfs(0);
    cout << (tot - dp[0][0]) << '\n';
}

