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
  // #define dbg(x...) pr("[", #x, "] = ["), pc(x);
}

#ifdef mikey 
using namespace output;
#else
using namespace output;
// #define dbg(x...)
#endif

const int MX = 200005;
const int MOD = (int) (1e9 + 7);
const ll INF = (ll) 1e18;

int main(){
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    vi a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    int q; cin >> q;
    while (q--) {
        int k; cin >> k;
        vi nxt(n);
        multiset<pi> vals;
        int p1 = 1, p2 = 1;
        vals.insert(mp(a[p2], p2));
        while (p2 < k) {
            ++p2;
            vals.insert(mp(a[p2], p2));
        }
        while (p1 < n && p2 < n) {
            // // dbg(p1, p2);
            // dbg(vals);
            auto it = vals.lb(mp(a[p1 - 1], INT_MIN));
            if (it == vals.begin()) {
                it = vals.end(); 
            }
            --it;
            // dbg(p1, *it);
            if (p1) nxt[p1 - 1] = (it -> s);
            vals.erase(vals.find(mp(a[p1], p1)));
            ++p1, ++p2;
            if (p2 < n) vals.insert(mp(a[p2], p2));
        }
        while (p1 < n) {
            // // dbg(p1, vals);
            auto it = vals.ub(mp(a[p1 - 1], INT_MIN));
            if (it == vals.end()) {
                it = vals.end(); 
            }
            --it;
            if (p1) nxt[p1 - 1] = (it -> s);
            vals.erase(vals.find(mp(a[p1], p1)));
            ++p1;    
        }
        int pos = 0;
        int prev = a[pos];
        int need = 0;
        while (pos < n - 1) {
            // // dbg(pos, nxt[pos]);
            pos = nxt[pos];
            // // dbg(prev, a[pos]);
            // // dbg(a[pos]);
            if (a[pos] >= prev) ++need;
            prev = a[pos];
        }
        cout << need << '\n';
    }
}

