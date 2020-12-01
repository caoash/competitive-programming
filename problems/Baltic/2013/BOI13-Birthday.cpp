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

const ll MX = 20000005;
const int MOD = (int) (1e9 + 7);
const int INF = (int) 987654321;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

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

int dp[MX];
int trans[MX];
bool has[MX];
int n, m; 
vector<int> prim;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        prim.pb(x);
    }
    for (int i = 0; i < n; i++) {
        for (int j = prim[i] - 1; j <= MX; j += prim[i]) {
            trans[j] = prim[i] - 1;
        }
    }
    for (int i = MX - 1; i >= 0; i--) {
        trans[i] = max(trans[i], trans[i + 1] - 1);
    }
    for (int i = 0; i < MX; i++) dp[i] = INF;
    dp[0] = 0;
    for (int i = 1; i < MX; i++) {
        int best = i - trans[i];
        if (best == INF) {
            dp[i] = INF;
        } else {
            dp[i] = min(INF, dp[best] + 1);
        }
    }
    for (int i = 0; i < m; i++) {
        int v; cin >> v;
        int ans = dp[v];
        if (ans == INF) cout << "oo" << '\n';
        else cout << ans << '\n';
    }
}

