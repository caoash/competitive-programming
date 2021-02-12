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

const int MX = 100005;

int dat[MX];

int ten(int x) {
    return ceil((double) x / (double) 10) * 10;
}

template < int SZ > struct DSU {
  int p[SZ], sz[SZ], sum[SZ], chaos[SZ];
  void init() {
    for (int i = 0; i < SZ; i++) {
      p[i] = i;
      sz[i] = 1;
      sum[i] = dat[i];
      chaos[i] = ten(dat[i]);
    }
  }
  int find(int x) {
    return p[x] = (p[x] == x ? x : find(p[x]));
  }
  void merge(int u, int v) {
    int a = find(u);
    int b = find(v);
    if (a != b) {
      if (sz[a] < sz[b]) {
        swap(a, b);
      }
      p[b] = a;
      sz[a] += sz[b];
      chaos[a] = ten(sum[a] + sum[b]);
      sum[a] += sum[b];
    }
  }
};

DSU<MX> dsu;
bool done[MX];

int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    ll ans = 0;
    FOR(i, n) {
        cin >> dat[i];
    }
    dsu.init();
    vector<int> ord(n);
    FOR(i, n) cin >> ord[i], ord[i]--;
    reverse(ord.begin(), ord.end());
    ll tot = 0;
    ll ccs = 0;
    auto merg = [&] (int i, int j) {
        int a = dsu.find(i);
        int b = dsu.find(j);
        tot -= dsu.chaos[a];
        tot -= dsu.chaos[b];
        dsu.merge(i, j);
        a = dsu.find(i);
        tot += dsu.chaos[a];
    };
    for (auto x : ord) {
        tot += ten(dat[x]);
        done[x] = true;
        int did = 0;
        if (x > 0 && done[x - 1]) merg(x - 1, x), ++did;
        if (x < n - 1 && done[x + 1]) merg(x, x + 1), ++did;
        if (did == 0) ++ccs;
        else if (did == 2) --ccs;
        ans = max(ans, tot * ccs);
        // dbg(x, tot * ccs);
    }
    cout << ans << '\n';
}

