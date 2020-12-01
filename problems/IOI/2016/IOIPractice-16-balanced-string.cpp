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

bool solve(vi a) {
    bool ag = false, bg = false;
    int chk = 0;
    for (int i = 0; i < sz(a); i++) {
        if (a[i] == a[(i + 1) % sz(a)]) {
            if (a[i]) bg = true;
            else ag = true;
        }
    }
    if (ag && bg) return false;
    else {
        if (bg) chk ^= 1;
        int siz = 0;
        vi ret;
        int pre = 0, suf = 0;
        bool seen = false;
        for (int i = 0; i < sz(a); i++) {
            if (a[i] == chk) ++pre;
            else break;
        }
        for (int i = sz(a) - 1; ~i; i--) {
            if (a[i] == chk) ++suf;
            else break;
        }
        for (int i = 0; i < sz(a); i++) {
            if (a[i] == chk && !seen) continue;
            if (a[i] == chk) {
                ++siz;
            } else {
                seen = true;
                if (siz) ret.pb(siz), siz = 0;
            }
        }
        ret.pb(pre + suf);
        set<int> vals;
        if (sz(ret) <= 1) return true;
        for (auto x : ret) {
            vals.insert(x);
        }
        if (sz(vals) > 2) return false;
        if (*(--vals.end()) - *(vals.begin()) > 1) return false;
        else {
            vi nvals;
            for (auto x : ret) {
                if (x == *(vals.begin())) {
                    nvals.pb(chk);
                } else {
                    nvals.pb(chk ^ 1);
                }
            }
            return solve(nvals);
        }
    }
}

int main(){
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t; cin >> t;
    while (t--) {
        string s; cin >> s;
        vi init;
        for (int i = 0; i < sz(s); i++) {
            if (s[i] == 'A') init.pb(0);
            else init.pb(1);
        }
        cout << solve(init) << '\n';
    }
}

