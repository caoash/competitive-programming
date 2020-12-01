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

const int MX = 500005;
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

int n;
int d[MX][2];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    for (int i = 1; i < n - 1; i++) cin >> d[i][0];
    for (int i = 1; i < n - 1; i++) cin >> d[i][1];
    bool bad = false;
    for (int i = 0; i < n - 1; i++) {
        if (abs(d[i][0] - d[i][1]) != abs(d[i + 1][0] - d[i + 1][1])) {
            bad = true;
        }
    }
    vector<array<int, 3>> ret;
    int diff = abs(d[0][0] - d[0][1]);
    if (!bad && diff != 0) {
        ret.pb({1, n, diff});
        for (int i = 1; i < n - 1; i++) {
            if (d[i][0] < d[i][1]) {
                ret.pb({1, i + 2, d[i][0]});
            } else {
                ret.pb({n, i + 2, d[i][1]});
            }
        }
        cout << "TAK\n";
        for (auto x : ret) {
            cout << x[0] << " " << x[1] << " " << x[2] << '\n';
        }
    } else {
        int sum = INT_MAX;
        for (int i = 1; i < n - 1; i++) {
            sum = min(sum, d[i][0] + d[i][1]);
        }
        d[0][0] = 0, d[0][1] = sum;
        d[n - 1][0] = sum, d[n - 1][1] = 0;
        vector<pi> vals;
        for (int i = 1; i < n - 1; i++) {
            if (d[i][0] + d[i][1] == sum) {
                vals.pb(mp(d[i][0], i + 1)); 
            }
        }
        sort(all(vals));
        int prev = 1;
        int last = 0;
        map<int, int> curr;
        for (auto x : vals) {
            ret.pb({prev, x.s, x.f - last});
            last = x.f, prev = x.s;
            curr[d[x.s - 1][1] - d[x.s - 1][0]] = x.s;
        }
        ret.pb({n, prev, sum - last});
        curr[sum] = 1;
        curr[-sum] = n;
        bool bad = false;
        for (int i = 1; i < n - 1; i++) {
            if (d[i][0] + d[i][1] != sum) {
                auto it = curr.find(d[i][1] - d[i][0]);
                if (it == curr.end()) {
                    bad = true;
                    // dbg(i, d[i][0], d[i][1]);
                } else {
                    // dbg(d[i][0], d[(it -> s) - 1][0]);
                    ret.pb({(it -> s), i + 1, d[i][0] - d[(it -> s) - 1][0]});
                }
            }
        }
        if (bad) {
            cout << "NIE\n";
        } else {
            cout << "TAK\n";
            for (auto x : ret) {
                cout << x[0] << " " << x[1] << " " << x[2] << '\n';
            }
        }
    }
}

