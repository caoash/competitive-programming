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

#ifdef mikey 
using namespace output;
#else
using namespace output;
#define dbg(x...)
#endif

const int MX = 200005;
const int MOD = (int) (1e9 + 7);
const ll INF = (ll) 1e18;

int n, k;
int dep[MX];
int sz[MX];
int has[MX];
vi adj[MX];

void dfs_init(int v, int p) {
    sz[v] = has[v];
    for (int to : adj[v]) {
        if (to != p) {
            dfs_init(to, v);
            sz[v] += sz[to];
        } 
    }
}

int find(int v, int p) { 
    for (int to : adj[v]) {
        if (to != p) {
            if (sz[to] > k) {
                return find(to, v);
            }
        }
    }
    return v;
}

set<pi> vals;
vi order;

void dfs_get(int v, int p) { 
    for (int to : adj[v]) {
        if (to != p) {
            dfs_get(to, v);
        }
    }
    if (has[v]) order.pb(v);
}

int ret[MX];
vi subt[MX];
vi good;

int main(){
#ifdef mikey
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> k;
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        u--, v--;
        adj[u].pb(v), adj[v].pb(u);
    }

    for (int i = 0; i < 2 * k; i++) {
        int x; cin >> x;
        x--;
        has[x] = 1;
        good.pb(x);
    }
    
    dfs_init(0, -1);
    int cent = find(0, -1);
    memset(ret, -1, sizeof(ret));
    int cnt = 0;
    for (int to : adj[cent]) {
        order.clear();
        dfs_get(to, cent);
        if (sz(order)) {
            vals.insert(mp(sz(order), cnt));
            for (auto x : order) {
                subt[cnt].pb(x);
            }
            ++cnt;
        }
    }
    pi guys = mp(-1, -1);
    set<pi> ans;
    while (sz(vals) >= 2) {
        auto fr = (prev(vals.end()));
        auto sec = (prev(prev(vals.end())));
        vals.erase(fr);
        vals.erase(sec);
        int v1 = subt[fr->s].back();
        int v2 = subt[sec->s].back();
        ret[v1] = v2;
        ret[v2] = v1;
        guys = mp(v1, v2);
        subt[fr->s].pop_back();
        subt[sec->s].pop_back();
        pi nxt_fr = mp((fr->f) - 1, fr->s);
        pi nxt_sec = mp((sec->f) - 1, sec->s);
        if (nxt_fr.f != 0) vals.insert(nxt_fr);
        if (nxt_sec.f != 0) vals.insert(nxt_sec);
    }
    if (has[cent]) {
        if (!vals.empty()) {
            pi fin = *(--vals.end());
            int nod = subt[fin.s].back();
            ret[nod] = cent;
            ret[cent] = nod;
        } else {
            // assert(guys.f != -1);
            // assert(n % 2 == 1);
            ret[guys.f] = cent; 
            ret[cent] = guys.s;
            ret[guys.s] = guys.f;
        }
    }
    for (auto x : good) {
        int a = x, b = ret[x];
        if (a > b) swap(a, b);
        ans.insert(mp(a, b));
    }
    cout << 1 << '\n';
    cout << cent + 1 << '\n';
    for (auto x : ans) {
        cout << x.f + 1 << " " << x.s + 1 << " " << cent + 1 << '\n'; 
    }
    cout << '\n';
}
