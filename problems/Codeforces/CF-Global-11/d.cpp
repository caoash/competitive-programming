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

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    vi a(n);
    for (auto &x : a) cin >> x;
    vector<vi> ops;
    auto sim = [&] (vi &moves) {
        vector<vi> na;
        int p = 0;
        for (auto x : moves) {
            vector<int> curr;
            for (int i = 0; i < x; i++) {
                curr.pb(a[p++]); 
            }
            na.pb(curr);
        }
        reverse(all(na));
        p = 0;
        for (auto x : na) {
            for (int v : x) {
                a[p++] = v;
            }
        }
        ops.pb(moves);
    };
    auto dist = [&] (int i, int j) {
        // dbg(i, j);
        assert(i <= j);
        return j - i + 1;
    };
    while (1) {
        pi curr = mp(-1, -1);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (a[j] == a[i] + 1) {
                    curr = mp(i, j); 
                }
            }
        }
        if (curr.f == -1) break;
        int ei = curr.s;
        for (int i = curr.s + 1; i < n; i++) {
            if (a[i] == a[i - 1] + 1) {
                ei = i;
            } else {
                break;
            }
        }
        vi vops;
        if (curr.s != 0) vops.pb(dist(0, curr.s - 1));
        vops.pb(dist(curr.s, ei));
        // dbg(curr.s, ei);
        vops.pb(dist(ei + 1, curr.f));
        if (curr.f != n - 1) vops.pb(dist(curr.f + 1, n - 1));
        sim(vops);
    }
    cout << sz(ops) << '\n';
    for (auto x : ops) {
        cout << sz(x) << " ";
        for (auto y : x) {
            cout << y << " ";
        }
        cout << '\n';
    }
}

