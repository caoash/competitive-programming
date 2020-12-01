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

ll mat[105][105];

void solve() {
    int n, m; cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> mat[i][j];
        }
    }
    map<pi, int> vals;
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int ox = n - i - 1;
            int oy = m - j - 1;
            if (vals.count(mp(ox, j))) {
                vals[mp(i, j)] = vals[mp(ox, j)];
                vals[mp(i, oy)] = vals[mp(ox, j)];
            } else if (vals.count(mp(i, oy))) {
                vals[mp(i, j)] = vals[mp(i, oy)];
                vals[mp(ox, j)] = vals[mp(i, oy)];
            } else {
                vals[mp(i, j)] = ++cnt;
                vals[mp(ox, j)] = cnt;
                vals[mp(i, oy)] = cnt;
            }
        }
    }
    vector<pi> rets[cnt + 1];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            rets[vals[mp(i, j)]].pb(mp(i, j));
        }
    }
    ll ans = 0;
    for (int i = 0; i <= cnt; i++) {
        ll best = INF;
        for (auto x : rets[i]) {
            ll req = 0;
            for (auto y : rets[i]) {
                req += abs(mat[x.f][x.s] - mat[y.f][y.s]);
            }
            best = min(best, req);
        }
        if (best != INF) ans += best;
    }
    cout << ans << '\n';
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T; cin >> T;
    while (T--) {
        solve();
    }
}

