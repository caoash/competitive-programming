#include <bits/stdc++.h> 
using namespace std;

typedef long long ll;

#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)

#define F first
#define S second

const int MX = 200005;

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
    p[root][0] = -1;
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
    int lift = b;
    for (int j = 31; j >= 0; j--) {
      if (lift & (1 << j)) {
        a = p[a][j];
        if (a == -1) break;
      }
    }
    return a;
  };
  int query2(int a, int b) {
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
  };
  bool is_anc(int a, int b) {
    return query2(a, b) == a;
  };
};

template < class T, int SZ > struct LazySeg {
  T tree[4 * SZ], lazy[4 * SZ];
  T merge(T a, T b) {
    return a + b;
  }
  void prop(int v, int l, int r) {
    if (lazy[v] != 0) {
      tree[v] += lazy[v];
      if (l != r) {
        lazy[2 * v + 1] += lazy[v];
        lazy[2 * v + 2] += lazy[v];
      }
      lazy[v] = 0;
    }
  }
  void update(int v, int l, int r, int ql, int qr, int x) {
    prop(v, l, r);
    if (r < ql || l > qr) {
      return;
    }
    if (l >= ql && r <= qr) {
      tree[v] += x;
      if (l != r) {
        lazy[2 * v + 1] += x;
        lazy[2 * v + 2] += x;
      }
      return;
    }
    int m = (l + r) / 2;
    update(2 * v + 1, l, m, ql, qr, x);
    update(2 * v + 2, m + 1, r, ql, qr, x);
    tree[v] = merge(tree[2 * v + 1], tree[2 * v + 2]);
  }

  T query(int v, int l, int r, int ql, int qr) {
    prop(v, l, r);
    if (l > qr || r < ql) {
      return 0;
    }
    if (l >= ql && r <= qr) {
      return tree[v];
    } else {
      int m = (l + r) / 2;
      T a = query(2 * v + 1, l, m, ql, qr);
      T b = query(2 * v + 2, m + 1, r, ql, qr);
      return merge(a, b);
    }
  }
};

int n;
map<int, int> smol[MX];
vector<int> adj[MX];
int a[MX];
LCA<MX> anc;
LazySeg<int, MX> subt, pars, blocked;
int st[MX], sz[MX];
map<int, vector<int>> cols;
int cnt = 0;

void dfs(int v, int p) {
    sz[v] = 1;
    st[v] = cnt++;
    for (int to : adj[v]) {
        if (to != p) {
            dfs(to, v);
            sz[v] += sz[to];
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    FOR(i, n) cin >> a[i];
    FOR(i, n - 1) {
        int u, v; cin >> u >> v;
        u--, v--;
        adj[u].push_back(v), adj[v].push_back(u);
        anc.addEdge(u, v);
    }
    anc.precomp(0);
    dfs(0, -1);
    FOR(i, n) cols[a[i]].push_back(i);
    for (auto x : cols) {
        vector<int> &cur = x.S;
        if (cur.size()) {
            for (auto y : cur) {
                subt.update(0, 0, n - 1, st[y], st[y], 1);
                pars.update(0, 0, n - 1, st[y], st[y] + sz[y] - 1, 1);
            }
            for (auto y : cur) {
                int num = subt.query(0, 0, n - 1, st[y], st[y] + sz[y] - 1);
                if (num != cur.size()) {
                    blocked.update(0, 0, n - 1, st[y], st[y] + sz[y] - 1, 1);
                }
                int def = pars.query(0, 0, n - 1, st[y], st[y]);
                int fpar = -1;
                int lo = 1, hi = n;
                while (lo <= hi) {
                    int mid = (lo + hi) / 2;
                    int cpar = anc.query(y, mid);
                    if (cpar == -1) hi = mid - 1;
                    else {
                        int uqry = pars.query(0, 0, n - 1, st[cpar], st[cpar]);
                        if (def - uqry > 1) {
                            hi = mid - 1;
                        } else if (a[cpar] == a[y]) {
                            hi = mid - 1;
                            fpar = cpar; 
                        } else {
                            lo = mid + 1;
                        }
                    }
                }
                if (fpar != -1) {
                    blocked.update(0, 0, n - 1, st[y], st[y] + sz[y] - 1, 1);
                    if (st[fpar] > 0) blocked.update(0, 0, n - 1, 0, st[fpar] - 1, 1);
                    if (st[fpar] + sz[fpar] < n) blocked.update(0, 0, n - 1, st[fpar] + sz[fpar], n - 1, 1);
                    blocked.update(0, 0, n - 1, st[fpar], st[fpar] + sz[fpar] - 1, 1);
                    for (auto to : adj[fpar]) {
                        if (to != anc.p[fpar][0]) {
                            if (anc.is_anc(to, y)) {
                                blocked.update(0, 0, n - 1, st[to], st[to] + sz[to] - 1, -1);
                            }
                        }
                    }
                }
            }
            for (auto y : cur) {
                subt.update(0, 0, n - 1, st[y], st[y], -1);
                pars.update(0, 0, n - 1, st[y], st[y] + sz[y] - 1, -1);
            }
        }
    }
    int ret = 0;
    FOR(i, n) {
        int ci = blocked.query(0, 0, n - 1, i, i);
        if (ci == 0) ++ret;
    }
    cout << ret << '\n';
}

