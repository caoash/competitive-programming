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

#ifdef mikey 
using namespace output;
#else
using namespace output;
#define dbg(x...)
#endif

int num[MX];
vi adj[MX];
vector<pi> eds;
vector<pi> gn[MX];
ll dpd[MX][2], dpu[MX][2];
int dep[MX];
pi anc[MX];
bool vis[MX];

void dfs_init(int v, int p) {
    for (int to : adj[v]) {
        if (to != p) {
            dep[to] = dep[v] + 1;
            dfs_init(to, v);
        }
    }
}

void dfs_dp(int v, int p) {
    dpd[v][0] = num[v];
    dpd[v][1] = num[v];
    // dbg(v, num[v]);
    for (auto to : gn[v]) {
        if (to.f == p) continue;
        anc[to.f] = mp(v, to.s);
        dfs_dp(to.f, v);
        if (to.s == 0) {
            dpd[v][0] += dpd[to.f][0];
        } else {
            dpd[v][1] += dpd[to.f][1];
        }
    }
}

int main(){
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> num[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        u--, v--;
        adj[u].pb(v), adj[v].pb(u);
        eds.pb(mp(u, v));
    }
    // dbg(eds);
    dfs_init(0, -1);
    for (auto x : eds) {
        if (dep[x.s] > dep[x.f]) {
            gn[x.f].pb(mp(x.s, 0));
            // dbg(x.f, x.s);
        } else {
            gn[x.s].pb(mp(x.f, 1));
            // dbg(x.s, x.f);
        }
    }
    dfs_dp(0, -1);
    queue<int> bfs;
    bfs.push(0);
    while (!bfs.empty()) {
        int curr = bfs.front();
        bfs.pop();
        for (auto to : gn[curr]) {
            if (to.f != anc[curr].f) {
                bfs.push(to.f);
            }
        }
        if (curr != 0) {
            if (anc[curr].s) {
                dpu[curr][0] = dpd[anc[curr].f][0];
                dpu[curr][1] = dpd[anc[curr].f][1] - dpd[curr][1];
            } else {
                dpu[curr][0] = dpd[anc[curr].f][0] - dpd[curr][0];
                dpu[curr][1] = dpd[anc[curr].f][1];
            }
            int tt = anc[anc[curr].f].s;
            if (tt == 0) dpu[curr][1] += dpu[anc[curr].f][1];
            else if (tt == 1) dpu[curr][0] += dpu[anc[curr].f][0];
        }
    }
    ll init = 0;
    for (int i = 0; i < n; i++) {
        // dbg(i, dpd[i][0], dpu[i][0]);
        ll tot = dpd[i][0];
        if (anc[i].s) tot += dpu[i][0];
        init += num[i] * (tot - 1);
        // dbg(num[i], dpd[i][0] + dpu[i][0]);
    }
    // dbg(init);
    // dbg(init);
    ll ans = 0;
    for (int i = 1; i < n; i++) {
        // dbg(i, anc[i].f, anc[i].s);
        if (anc[i].s) {
            // dbg(i, dpd[i][0], dpu[i][1]);
            ans = max(ans, init + (dpd[i][0] * dpu[i][1]));
        } else {
            // dbg(i, dpd[i][1], dpu[i][0]);
            ans = max(ans, init + (dpd[i][1] * dpu[i][0]));
        }
    }
    cout << ans << '\n';
}

