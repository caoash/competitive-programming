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
#define F first
#define S second
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
    pr("{", x.F, ", ", x.S, "}");
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

vi adj[MX];
int n, s, k;
int add = 0;
map<pi, int> good[MX];
set<pi> bad[MX];

void dfs(int v, int p, int d) { 
    for (int to : adj[v]) {
        if (to != p) {
            dfs(to, v, d + 1);
        }
    }
    for (int to : adj[v]) {
        if (to != p) {
            if (sz(good[v]) < sz(good[to])) swap(good[v], good[to]);
            for (auto x : good[to]) good[v][x.F] += x.S;
            good[to].clear();
            if (sz(bad[v]) < sz(bad[to])) swap(bad[v], bad[to]);
            for (auto x : bad[to]) bad[v].insert(x);
            bad[to].clear();
        }
    }
    // dbg(v + 1, good[v], bad[v]);
    {
        vector<pi> todel;
        for (auto last = bad[v].rbegin(); last != bad[v].rend(); last++) {
            // dbg(*last);
            /*
             * dep1
             * dep2
             * dep2 <= k - dep1 + 2 * d
             */
            auto kil = good[v].ub(mp(k - last->F + 2 * d, INT_MAX));
            if (kil != good[v].begin()) {
                --kil;
                todel.pb(*last);
                good[v][kil->F]--;
                if (good[v][kil->F] == 0) good[v].erase(kil);
            }
        }
        // dbg(todel);
        for (auto x : todel) bad[v].erase(x);
    }
    // dbg(v + 1, bad[v]);
    auto it = good[v].ub(mp(d + k, INT_MAX));
    if (it != good[v].begin()) {
        --it;
        good[v][it->F]--;
        if (good[v][it->F] == 0) good[v].erase(it);
    } else {
        bad[v].insert(mp(d, v));
    }
    int need = 0;
    while (!bad[v].empty()) {
        auto last = --bad[v].end();
        assert(last->F <= d + k);
        if (last->F == d + k || v == 0 || (need % s)) bad[v].erase(last), ++need;
        else break;
    }
    int tot = (need / s) + ((need % s) > 0);
    int rem = (tot * s) - need; 
    // dbg(v+1, need, tot, rem);
    // dbg(s, need, rem);
    if (need) {
        good[v][mp(d, v)] = rem, add += tot;
        if (rem == 0) good[v].erase(mp(d, v));
    }
    // dbg(v + 1, good[v], bad[v]);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> s >> k;
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        u--, v--;
        adj[u].pb(v), adj[v].pb(u);
    }
    dfs(0, -1, 0);
    cout << add << '\n';
}

