#pragma GCC optimize ("Ofast")
#pragma GCC target ("avx2")

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
const int INF = (int) 1e9;

int sushi(int n, int b, vi a) {
    pi dp[2][b + 1];
    for (int i = 1; i <= b; i++) dp[0][i] = mp(INF, INF);
    dp[0][0] = mp(0, 0);
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= b; j++) {
            dp[i & 1][j] = mp(INF, INF);
            if (dp[(i & 1) ^ 1][j].s != INF) {
                dp[i & 1][j] = min(dp[i & 1][j], mp(0, dp[(i & 1) ^ 1][j].s));
            }
            if (j - a[i - 1] >= 0) {
                int nv = dp[i & 1][j - a[i - 1]].f + 1;
                dp[i & 1][j] = min(dp[i & 1][j], mp(nv, max(dp[i & 1][j - a[i - 1]].s, nv)));
            }
            dbg(i, j, dp[i & 1][j]);
        }
    }
    return dp[n & 1][b].s;
};

int main(){
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, b; cin >> n >> b;
    vi a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    cout << sushi(n, b, a) << '\n';
}
