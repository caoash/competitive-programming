#include <bits/stdc++.h> 
using namespace std;
 
typedef long long ll;
 
#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)
 
#define F first
#define S second

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
  // #define dbg(x...) pr("[", #x, "] = ["), pc(x);
}

#ifdef mikey 
using namespace output;
#else
using namespace output;
// #define dbg(x...)
#endif

const int MX = 2000005;

int cnt[2][2][32][2]; // in or out, bit, one or zero
bool req[32];
 
int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);    
    int n, m; cin >> n >> m;
    vector<int> a(m);
    FOR(i, m) cin >> a[i];
    FOR(i, n) {
        int v = 0;
        FOR(j, m) {
            if (a[j] & (1 << i)) {
                v |= 1;
            } else {
                v |= 2;
            }
        }
        if (v == 3) req[i] = true;
    }
    auto upd = [&] (int x, int v, int c, int t) {
        // dbg("UPD", x, v, c);
        FOR(i, n) {
            if (x & (1 << i)) {
                cnt[t][v][i][1] += c;
            } else {
                cnt[t][v][i][0] += c;
            }
        }
    };
    auto gud = [&] (int v, int t) {
        FOR(i, n) {
            if (req[i] && (cnt[t][v][i][0] == 0 || cnt[t][v][i][1] == 0)) {
                return false;
            }
        }
        return true;
    };
    int l = 0, r = 0;
    FOR(i, m) {
        upd(a[i], (i > 0), 1, 0);
        upd(a[i], (i > 0), 1, 1);
    }
    ll ans = 0;
    FOR(i, m) {
        while (!gud(0, 0) && l < m - 1) {
            ++l;
            upd(a[l], 1, -1, 0);
            upd(a[l], 0, 1, 0);
        }
        while (gud(1, 1) && r < m - 1) {
            ++r; 
            upd(a[r], 1, -1, 1);
            upd(a[r], 0, 1, 1);
        }
        upd(a[i], 0, -1, 0);
        upd(a[i], 0, -1, 1);
        upd(a[i], 1, 1, 0);
        upd(a[i], 1, 1, 1);
        // dbg(i, l, r);
        ans += max(r - l, 0);
    }
    cout << ans << '\n';
}

