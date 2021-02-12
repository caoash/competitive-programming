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

multiset<int> adj[7];
map<pi, vi> ind;
vi order;

void euler(int v) {
    while (!adj[v].empty()) {
        int to = *(adj[v].begin());
        adj[v].erase(adj[v].find(to));
        adj[to].erase(adj[to].find(v));
        euler(to);
    }
    order.pb(v);
}

int main(){
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N; cin >> N;
    vi deg(7);
    for (int i = 0; i < N; i++) {
        int u, v; cin >> u >> v;
        ind[mp(u, v)].pb(i);
        adj[u].insert(v), adj[v].insert(u);
        ++deg[u], ++deg[v];
    }
    int od = 0;
    int odv = -1;
    for (int i = 0; i <= 6; i++) {
        if (deg[i] > 0) odv = i;
    }
    for (int i = 0; i <= 6; i++) {
        if (deg[i] % 2) ++od, odv = i;
    }
    if ((od == 0 || od == 2) && odv != -1) {
        euler(odv);
        reverse(all(order));
        vector<pi> things;
        vector<pi> ret;
        for (int i = 1; i < sz(order); i++) things.pb(mp(order[i - 1], order[i]));
        for (auto x : things) {
            if (!ind[x].empty()) {
                ret.pb(mp(ind[x].back() + 1, 0));
                ind[x].pop_back();
            } else {
                if (!ind[mp(x.s, x.f)].empty()) {
                    ret.pb(mp(ind[mp(x.s, x.f)].back() + 1, 1));
                    ind[mp(x.s, x.f)].pop_back();
                } else {
                    assert(true);
                }
            }
        }
        if (sz(ret) < N) {
            cout << "No solution\n";
        } else {
            for (int i = 0; i < sz(ret); i++) {
                cout << ret[i].f << " " << (ret[i].s ? "- " : "+ ") << '\n';
            }
        }
    } else {
        cout << "No solution\n";
    }
}

