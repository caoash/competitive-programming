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

ll a[MX];

template < int SZ > struct DSU {
  int p[SZ], sz[SZ];
  set<int> vals[SZ];
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
      for (auto x : vals[b]) {
        vals[a].insert(x);
      }
      vals[b].clear();
    }
  }
  int gmx(int x) {
      int y = find(x);
      vals[y].insert(a[x]);
      if (vals[y].empty()) return 0;
      auto it = (--vals[y].end());
      return *it;
  }
};

DSU<MX> dsu;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m, q; cin >> n >> m >> q;
    for (int i = 0; i < n; i++) cin >> a[i];
    vector<pi> edges;
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--, v--;
        edges.pb(mp(u, v));
    }
    vector<pi> qrys;
    vector<bool> done(m);
    vector<bool> used(n);
    int cnt = 0;
    for (int i = 0; i < q; i++) {
        int qt, qn; cin >> qt >> qn;
        qn--;
        qrys.pb(mp(qt, qn));
        if (qt == 2) {
            done[qn] = true;
        }
        else {
            used[qn] = true;
            ++cnt;
        }
    }
    for (int i = 0; i < m; i++) {
        if (!done[i]) qrys.pb(mp(2, i));
    }
    for (int i = 0; i < n; i++) {
        if (!used[i]) qrys.pb(mp(1, i));
    }
    dsu.init();
    reverse(all(qrys));
    vi ans;
    for (auto x : qrys) {
        dbg(x);
        if (x.f == 1) {
            int v = dsu.gmx(x.s);
            dbg("MX", x.s, v);
            ans.pb(v);
        }
        else {
            int u = edges[x.s].f, v = edges[x.s].s;
            if (dsu.find(u) != dsu.find(v)) {
                dbg("MERGING", u, v);
                dsu.merge(u, v);
            }
        }
    }
    reverse(all(ans));
    for (int i = 0; i < cnt; i++) {
        cout << ans[i] << '\n';
    }
    cout << '\n';
}

