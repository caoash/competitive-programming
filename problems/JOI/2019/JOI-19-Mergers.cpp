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

const int MX = 500005;
const int MOD = (int) (1e9 + 7);
const ll INF = (ll) 1e18;

namespace output {
  void pr(int x) {
    cout << x;
  }
  void pr(long x) {
    cout << x;
  }
  void pr(ll x) {
    cout << x;
  }
  void pr(unsigned x) {
    cout << x;
  }
  void pr(unsigned long x) {
    cout << x;
  }
  void pr(unsigned long long x) {
    cout << x;
  }
  void pr(float x) {
    cout << x;
  }
  void pr(double x) {
    cout << x;
  }
  void pr(long double x) {
    cout << x;
  }
  void pr(char x) {
    cout << x;
  }
  void pr(const char * x) {
    cout << x;
  }
  void pr(const string & x) {
    cout << x;
  }
  void pr(bool x) {
    pr(x ? "true" : "false");
  }

  template < class T1, class T2 > void pr(const pair < T1, T2 > & x);
  template < class T > void pr(const T & x);

  template < class T, class...Ts > void pr(const T & t,
    const Ts & ...ts) {
    pr(t);
    pr(ts...);
  }
  template < class T1, class T2 > void pr(const pair < T1, T2 > & x) {
    pr("{", x.f, ", ", x.s, "}");
  }
  template < class T > void pr(const T & x) {
    pr("{"); // const iterator needed for vector<bool>
    bool fst = 1;
    for (const auto & a: x) pr(!fst ? ", " : "", a), fst = 0;
    pr("}");
  }

  void ps() {
    pr("\n");
  } // print w/ spaces
  template < class T, class...Ts > void ps(const T & t,
    const Ts & ...ts) {
    pr(t);
    if (sizeof...(ts)) pr(" ");
    ps(ts...);
  }

  void pc() {
    cout << "]" << endl;
  } // debug w/ commas
  template < class T, class...Ts > void pc(const T & t,
    const Ts & ...ts) {
    pr(t);
    if (sizeof...(ts)) pr(", ");
    pc(ts...);
  }
  // #define dbg(x...) pr("[", #x, "] = ["), pc(x);
}

#ifdef mikey 
using namespace output;
#else
using namespace output;
// #define dbg(x...)
#endif

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
};

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

vi adj[MX], sadj[MX];
int col[MX];
int pull[MX], dep[MX];
vi nods[MX];
LCA<MX> anc;
DSU<MX> dsu;
int deg[MX];

void dfs_pull(int v, int p) {
    for (int to : adj[v]) {
        if (to != p) {
            dep[to] = dep[v] + 1;
            dfs_pull(to, v);
            pull[v] += pull[to]; 
        }
    }
}

int main(){
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, k; cin >> n >> k;
    vector<pi> eds;
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        u--, v--;
        adj[u].pb(v), adj[v].pb(u);
        anc.addEdge(u, v);
        eds.pb(mp(u, v));
    }
    anc.precomp();
    auto upd = [&] (int i, int j) {
        // dbg(i, j);
        int lca = anc.query(i, j);
        pull[i]++, pull[j]++;
        pull[lca] -= 2;
    };
    for (int i = 0; i < n; i++) {
        cin >> col[i];
        col[i]--;
        nods[col[i]].pb(i);
        // dbg(i, col[i]);
    }
    for (int c = 0; c < k; c++) {
        if (nods[c].empty()) continue;
        // dbg(c, nods[c]);
        int fir = nods[c][0];
        for (int j = 1; j < sz(nods[c]); j++) {
            int sec = nods[c][j]; 
            upd(fir, sec);
        }
    }
    dfs_pull(0, -1);
    dsu.init();
    for (auto x : eds) {
        if (dep[x.f] > dep[x.s]) swap(x.f, x.s);
        if (pull[x.s]) {
            dsu.merge(x.f, x.s);
        } 
    }
    for (auto x : eds) {
        if (dep[x.f] > dep[x.s]) swap(x.f, x.s);
        if (pull[x.s]) continue;
        int u = dsu.find(x.f), v = dsu.find(x.s);
        deg[u]++, deg[v]++;
        // dbg(x.f + 1, x.s + 1, pull[x.s]);
    }
    set<int> leaf;
    for (int i = 0; i < n; i++) {
        if (deg[dsu.find(i)] == 1) leaf.insert(dsu.find(i));
    }
    // dbg(leaf);
    cout << ((sz(leaf) + 1) / 2) << '\n';
}
