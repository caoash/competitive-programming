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
using pii = pair<pi, int>;
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

map<pi, vector<pii>> adj;
map<pi, ll> ret;
set<pi> vis;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m; cin >> n >> m;
    pi sx, ex;
    cin >> sx.f >> sx.s;
    cin >> ex.f >> ex.s;
    vector<pi> a(m), b(m);
    for (int i = 0; i < m; i++) {
        cin >> a[i].f >> a[i].s;
        b[i].s = a[i].f;
        b[i].f = a[i].s;
    }
    sort(all(a));
    sort(all(b));
    auto dist = [&](pi a, pi b) {
        return min(abs(a.f - b.f), abs(a.s - b.s));
    };
    auto manh = [&](pi a, pi b)  {
        return abs(a.f - b.f) + abs(a.s - b.s);
    };
    auto add = [&] (pi u, pi v, int d) {
        if (d == 0) {
            adj[u].pb(mp(v, dist(u, v)));
        } else {
            adj[u].pb(mp(v, manh(u, v)));
        }
    };
    auto op = [&] (pi x) {
        return mp(x.s, x.f);
    };
    for (int i = 0; i < m - 1; i++) {
        add(a[i], a[i + 1], 0);
        add(a[i + 1], a[i], 0);
        add(op(b[i]), op(b[i + 1]), 0);
        add(op(b[i + 1]), op(b[i]), 0);
        ret[a[i]] = INF;
    }
    if (m != 0) ret[a[m - 1]] = INF;
    for (int i = 0; i < m; i++) {
        add(sx, a[i], 0);
        add(a[i], sx, 1);
        add(a[i], ex, 1);
    }
    add(sx, ex, 1);
    ret[sx] = 0;
    if (sx != ex) ret[ex] = INF;
    priority_queue<pair<ll, pi>, vector<pair<ll, pi>>, greater<pair<ll, pi>>> pq;
    pq.push(mp(0, sx));
    while (!pq.empty()) {
        pair<ll, pi> fr = pq.top();
        pi curr = fr.s;
        pq.pop();
        for (auto x : adj[curr]) {
            if (!vis.count(x.f))  {
                if (ret[x.f] > ret[curr] + x.s) {
                    ret[x.f] = ret[curr] + x.s;
                    pq.push(mp(ret[x.f], x.f));
                }
            }
        }
        vis.insert(curr);
    }
    cout << ret[ex] << '\n';
}

