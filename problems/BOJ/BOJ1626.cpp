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

const int MX = 50005;
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
  #define dbg(x...) pr("[", #x, "] = ["), pc(x);
}

#ifdef LOCAL
using namespace output;
#endif

template < int SZ > struct LCA {
  int depth[SZ];
  int p[SZ][33];
  int pmx[SZ][33];
  int smx[SZ][33];
  vector<pi> adj[SZ];
  void addEdge(int u, int v, int w) {
    adj[u].push_back(mp(v, w));
    adj[v].push_back(mp(u, w));
  }
  void dfs(int v, int par) {
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
        smx[i][j] = -1;
      }
    }
    p[0][0] = 0;
    pmx[0][0] = 0;
    dfs(0, -1);
    for (int j = 1; j < 32; j++) {
      for (int i = 0; i < SZ; i++) {
        if (p[i][j - 1] == -1) {
          p[i][j] = -1;
          pmx[i][j] = -1;
        } else {
          p[i][j] = p[p[i][j - 1]][j - 1];
          pmx[i][j] = max(pmx[i][j - 1], pmx[p[i][j - 1]][j - 1]);
          smx[i][j] = max(smx[i][j - 1], smx[p[i][j - 1]][j - 1]);
          if (pmx[i][j - 1] != pmx[p[i][j - 1]][j - 1]) {
            smx[i][j] = max(smx[i][j], min(pmx[i][j - 1], pmx[p[i][j - 1]][j - 1]));
          }
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
  int query2(int a, int b, int best) {
    int ans = 0;
    auto chk = [&] (int i, int j) {
        if (pmx[i][j] == best) {
            ans = max(ans, smx[i][j]);
        }
        else {
            ans = max(ans, pmx[i][j]);
        }
    };
    if (depth[a] > depth[b]) {
        swap(a, b);
    }
    int lift = depth[b] - depth[a];
    for (int j = 31; j >= 0; j--) {
        if (lift & (1 << j)) {
            chk(b, j);
            b = p[b][j];
        }
    }
    for (int j = 31; j >= 0; j--) {
        if (p[a][j] != p[b][j]) {
            chk(a, j);
            chk(b, j);
            a = p[a][j];
            b = p[b][j];
        }
    }
    if (a != b) {
        chk(a, 0);
        chk(b, 0);
    }
    return ans;
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

vector<pair<int, pi>> edges;
vector<pair<int, pi>> bad;

DSU<MX> dsu;
LCA<MX> lca;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m; cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w;
        u--, v--;
        edges.pb(mp(w, mp(u, v)));
    }
    dsu.init();
    sort(all(edges));
    ll cost = 0;
    int num = 0;
    for (auto x : edges) {
        if (dsu.find(x.s.f) != dsu.find(x.s.s)) {
            // dbg(x.s.f, x.s.s);
            dsu.merge(x.s.f, x.s.s);
            lca.addEdge(x.s.f, x.s.s, x.f);
            ++num;
            cost += x.f;
        }
        else {
            bad.pb(x);
        }
    }
    if (num != n - 1) {
        cout << -1 << '\n';
        return 0;
    }
    lca.precomp();
    ll ans = INF;
    for (auto x : bad) {
        int curr = lca.query(x.s.f, x.s.s);
        if (curr == x.f) {
            curr = lca.query2(x.s.f, x.s.s, curr);
        }
        ans = min(ans, cost - curr + x.f);
    }
    cout << (ans == INF ? -1 : ans) << '\n';
}

