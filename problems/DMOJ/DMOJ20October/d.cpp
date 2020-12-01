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
          res.mat[i][j] += mat[i][k] * mat2.mat[k][j];
          if (res.mat[i][j] >= MOD) {
            res.mat[i][j] %= MOD;
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
    assert(sz(a) == b.sz);
    vector < ll > res(sz(a));
    for (int i = 0; i < b.sz; i++) {
      for (int j = 0; j < sz(a); j++) {
        res[i] += (a[j] * b.mat[i][j]);
        if (res[i] >= MOD) {
          res[i] %= MOD;
        }
      }
    }
    return res;
  }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll N, K; 
    int T; 
    ll C; 
    cin >> N >> K >> T >> C;
    vector<ll> init(101);
    init[0] = C;
    Matrix<101, MOD> mat;
    mat.mat[0][0] = 1;
    for (int i = 0; i < T; i++) {
        mat.mat[i][i + 1] = 1;
    }
    mat.mat[T][0] = K;
    // dbg("INIT: ");
    // for (int i = 0; i <= T; i++) cout << init[i] << " ";
    // cout << '\n';
    Matrix<101, MOD> fin = mat.pow(mat, N - 1);
    vector<ll> res = mat.mult_v(init, fin);
    // dbg("RES: ");
    // for (int i = 0; i <= T; i++) cout << res[i] << " ";
    // cout << '\n';
    ll ans = 0;
    ans += (res[0] * 2) % MOD;
    ans %= MOD;
    for (int i = 1; i <= T; i++) {
        ans += res[i];
        ans %= MOD;
    }
    cout << ans << '\n';
}

