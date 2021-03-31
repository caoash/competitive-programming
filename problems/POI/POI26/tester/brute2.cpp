#include <bits/stdc++.h> 
#include <assert.h>
#include <cstring>
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

template < int SZ, int MOD > struct Matrix {
  ll mat[SZ][SZ];
  int sz = SZ;
  Matrix() {
    memset(mat, 0, sizeof(mat));
  }
  Matrix operator * (const Matrix & mat2) {
    Matrix res;
    for (int i = 0; i < SZ; i++) {
      for (int j = 0; j < SZ; j++) {
        for (int k = 0; k < SZ; k++) {
          res.mat[i][j] += (mat[i][k] * mat2.mat[k][j]) % MOD;
          if (res.mat[i][j] >= MOD) {
            res.mat[i][j] -= MOD;
          }
        }
      }
    }
    return res;
  }
  ll * operator[](const int & i) {
    return mat[i];
  }
  Matrix id() {
    Matrix nmat;
    for (int i = 0; i < SZ; i++) {
      nmat.mat[i][i] = 1;
    }
    return nmat;
  };
  Matrix pow(Matrix & a, ll p) {
    Matrix res = id();
    while (p) {
      if (p & 1) res = res * a;
      a = a * a;
      p >>= 1;
    }
    return res;
  }
  vector < ll > mult_v(const vector < ll > & a,
    const Matrix & b) {
    assert(a.size() == b.sz);
    // assert(sz(a) == b.sz);
    vector < ll > res(a.size());
    for (int i = 0; i < b.sz; i++) {
      for (int j = 0; j < a.size(); j++) {
        res[i] += (a[j] * b.mat[i][j]) % MOD;
        if (res[i] >= MOD) {
          res[i] -= MOD;
        }
      }
    }
    return res;
  }
};

const int MOD = 1e9 + 9;
const int MX = 55;

Matrix<MX, MOD> ways;
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);    
    int n, m, k; cin >> n >> m >> k;
    vector<bool> init(n);
    FOR(i, k) {
        int x; cin >> x;
        x--;
        init[x] = true;
    }
    // cout << 1 << endl;
    FOR(i, m) {
        int u, v; cin >> u >> v;
        u--, v--;
        // cout << u << " " << v << endl;
        ways.mat[u][v] = 1;
    }
    auto worksEh = [&] (ll mid) {
        Matrix<MX, MOD> cp;
        // Matrix<MX, MOD> res = ways.pow(ways, mid);
        // cout << "MID: " << mid << '\n';
        FOR(i, n) {
            FOR(j, n) {
                cp.mat[i][j] = ways.mat[i][j];
                // cout << ways.mat[i][j] << " ";
            }
            // cout << '\n';
        }
        cp = cp.pow(cp, mid);
        /*
        FOR(i, n) {
            FOR(j, n) {
                cout << cp.mat[i][j] << " ";
            }
            cout << '\n';
        }
        */
        vector<int> places;
        FOR(i, n) {
            bool good = true;
            FOR(j, n) {
                if (init[j] && cp.mat[j][i] == 0) {
                    good = false;
                }
            }
            if (good) places.push_back(i);
        }
        // dbg(mid);
        return (places.size() > 0);
    };
    int ans = 0;
    FOR(i, 105) {
        if (worksEh(i)) {
            ans = i; 
            break;
        }
    }
    cout << ans << endl;
    /*
    ll lo = 0, hi = 1e6;
    ll ans = -1;
    while (lo <= hi) {
        ll mid = (lo + hi) / 2;
        if (worksEh(mid)) {
            ans = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    if (ans != -1) {
        cout << "TAK\n";
        cout << ans << '\n';
    } else {
        cout << "NIE\n";
    }
    */
}

