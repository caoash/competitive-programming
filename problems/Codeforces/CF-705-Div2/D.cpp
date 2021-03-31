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
  #define dbg(x...) pr("[", #x, "] = ["), pc(x);
}

#ifdef mikey 
using namespace output;
#else
using namespace output;
#define dbg(x...)
#endif

const int MX = 200005;
const int MOD = 1e9 + 7;

map<int, int> cnt[MX];
int uq[MX];
 
int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);    
    int n, q; cin >> n >> q;
    vector<int> a(n);
    FOR(i, n) cin >> a[i];
    ll ans = 1;
    auto ad = [&] (int i, int j) {
        cnt[i][j]++;
        if (cnt[i][j] == 1) {
            uq[j]++;
            if (uq[j] == n) {
                ans *= j;
                ans %= MOD;
                FOR(k, n) {
                    cnt[k][j]--;
                    if (cnt[k][j] == 0) uq[j]--;
                }
            }
        }
    };
    FOR(i, n) {
        ll v = a[i];
        for (ll j = 2; j * j <= v; j++) {
            while (v % j == 0) {
                ad(i, j);
                v /= j;
            }
        }
        if (v > 1) {
            ad(i, v);
        }
    }
    FOR(i, q) {
        int p; ll x; cin >> p >> x;
        p--;
        ll v = x;
        for (ll j = 2; j * j <= v; j++) {
            while (v % j == 0) {
                ad(p, j);
                v /= j;
            }
        }
        if (v > 1) {
            ad(p, v);
        }
        cout << ans << '\n';
    }
}

/*
 * 1 6 8 12
 *
 * 2 3 
 * 3 3
 * 2 2 3
 * 2 3
 *
 * 2
 */

