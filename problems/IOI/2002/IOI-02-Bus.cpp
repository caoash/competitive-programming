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

const int MX = 505;
const int MOD = (int) (1e9 + 7);
const int INF = 1e9;

int n;
vector<pi> pts;

int dist(pi a, pi b) {
    return abs(a.f - b.f) + abs(a.s - b.s);
}

int solve(int a, int b) {
    vector<pi> df;
    int fix = dist(pts[a], pts[b]);
    for (int i = 0; i < n; i++) {
        df.pb(mp(dist(pts[i], pts[a]), dist(pts[i], pts[b])));
    }
    sort(all(df));
    reverse(all(df));
    dbg(df);
    int cans = INF;
    int prev = INF;
    array<int, 4> best;
    for (int i = 0; i < 4; i++) best[i] = 0;
    auto relax = [&] () {
        int ret = -1; 
        ret = max(ret, best[0] + fix + best[2]);
        ret = max(ret, best[0] + best[1]);
        ret = max(ret, best[2] + best[3]);
        if (ret == -1) return INF;
        return ret;
    };
    auto upd = [&] (int v) {
        if (v > best[2]) best[3] = best[2], best[2] = v;
        else if (v > best[3]) best[3] = v;
    };
    for (int i = 0; i < n; i++) {
        prev = INF;
        best[0] = df[i].f;
        best[1] = 0;
        for (int j = i + 1; j < n; j++) {
            best[1] = df[j].f;
            int cr = relax();
            if (cr > prev) {
                upd(df[i].s);
                i = j - 1;
                break;
            } else {
                cans = min(cans, cr);
            }
            upd(df[j].s);
            if (j == i + 1) prev = cr;
            if (j == n - 1) {
                dbg("UPD", i);
                upd(df[i].s);
                i = j - 1;
                break;
            }
        }
    }
    cans = min(cans, relax());
    return cans;
}

int main(){
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for (int i = 0; i < n; i++) {
        int xi, yi; cin >> xi >> yi;
        pts.pb(mp(xi, yi));
    }
    int ans = INF;
    ans = solve(2, 3);
    /*
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double st = clock();
            int ret = solve(i, j);
            dbg(i, j, ret);
            ans = min(ans, ret);
            double en = clock();
            dbg(i, j, (double)(en - st) / CLOCKS_PER_SEC);
        }
    }
    */
    cout << ans << '\n';
    
}

