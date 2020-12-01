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

const int MX = 200005;
const int MOD = (int) (1e9 + 7);
const ll INF = (ll) 1e18;

void solve() {
    int n, k; cin >> n >> k;
    string s; cin >> s;
    int prev = -1;
    vector<int> gaps;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'W') {
            if (prev != -1) gaps.pb(i - prev - 1);
            prev = i;
        }
    }
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'W') {
            ++ans;
            if (i > 0 && s[i - 1] == 'W') {
                ++ans;        
            }
        }
    }
    sort(all(gaps));
    for (auto x : gaps) {
        if (x == 0 || k == 0) continue;
        ans += 2 * min(k, x - 1);
        k -= min(k, x - 1);
        if (k) {
            ans += 3;
            k--;
        }
    }
    int pre = 0, suf = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] != 'L') break;
        ++pre;
    }
    for (int i = n - 1; i >= 0; i--) {
        if (s[i] != 'L') break;
        ++suf;
    }
    // dbg(pre, suf);
    if (pre == n) {
        if (k) {
            k--;
            ++ans;
        }
        ans += 2 * min(k, pre - 1);
    } else {
        ans += 2 * min(k, pre);
        k -= min(k, pre);
        ans += 2 * min(k, suf); 
        k -= min(k, suf);
    }
    cout << ans << '\n';
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t; cin >> t;
    while (t--) {
        solve();
    }
}

