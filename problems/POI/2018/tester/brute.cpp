#include <bits/stdc++.h> 
using namespace std;

typedef long long ll;

#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)

#define F first
#define S second

const int MX = 100005;

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

LCA<MX> anc;

vector<int> adj[MX];
int deg[MX];
bool marked[MX];
int dist[MX];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, k; cin >> n >> k;
    FOR(i, n - 1) {
        int u, v; cin >> u >> v;
        u--, v--;
        adj[u].push_back(v), adj[v].push_back(u);
        anc.addEdge(u, v);
        deg[u]++, deg[v]++;
    }
    anc.precomp(0);
    pair<int, int> best = {1e9, 1e9};
    int res = 0;
    FOR(mask, (1 << n)) {
        FOR(j, n) dist[j] = 1e9, marked[j] = false;
        int num = __builtin_popcount(mask);
        if (num > k || num <= 1) continue;
        vector<int> marx;
        FOR(j, n) {
            if (mask & (1 << j)) {
                marked[j] = true;
                marx.push_back(j);
            }
        }
        FOR(j, marx.size()) F0R(l, j + 1, marx.size()) {
            int a = marx[j], b = marx[l];
            int lca = anc.query(a, b);
            while (a != lca) {
                a = anc.p[a][0];
                marked[a] = true;
            }
            while (b != lca) {
                b = anc.p[b][0];
                marked[b] = true;
            }
        }
        queue<int> bfs;
        FOR(j, n) {
            if (marked[j]) bfs.push(j), dist[j] = 0;
        }
        while (!bfs.empty()) {
            int curr = bfs.front();
            bfs.pop();
            for (int to : adj[curr]) {
                if (dist[to] > dist[curr] + 1) {
                    dist[to] = dist[curr] + 1;
                    bfs.push(to);
                }
            }
        }
        int ans = 0;
        FOR(i, n) ans = max(ans, dist[i]);
        if (make_pair(ans, num) < best) {
            best = min(best, make_pair(ans, num));   
            res = mask;
        }
    }
    cout << best.F << " " << best.S << '\n';
    // FOR(i, n) if (res & (1 << i)) cout << i + 1 << " ";
    // cout << '\n';
}

