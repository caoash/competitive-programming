#include <cmath>
#include <functional>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <set>
#include <map>
#include <list>
#include <time.h>
#include <math.h>
#include <random>
#include <deque>
#include <queue>
#include <cassert>
#include <unordered_map>
#include <unordered_set>
#include <iomanip>
#include <bitset>
#include <sstream>
#include <chrono>
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

const int MX = 200005;
const int MXV = 10;

int vals[MX];
ll res[MX];
vector<pair<int, int>> qrs[MX];
int rt[MX];
int n, q;

template < int SZ > struct DSU {
  int p[SZ], sz[SZ];
  int small[SZ];
  void init() {
    for (int i = 0; i < SZ; i++) {
      p[i] = i;
      sz[i] = 1;
      small[i] = vals[i];
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
      small[a] = min(small[a], small[b]);
    }
  }
  int gmn(int x) {
    return small[find(x)];
  }
};

template<class T, int SZ> struct BIT {
    T bit[SZ + 1];
    void upd(int p, int x) {
        p++;
        for (; p <= SZ; p += (p & -p)) bit[p] += x;
    }
    T sum(int r) {
        T ret = 0;
        for (; r; r -= (r & -r)) ret += bit[r];
        return ret;
    }
    T query(int l, int r) {
        l++, r++;
        return sum(r) - sum(l - 1); 
    }
};

template < class T, int SZ > struct LazySeg {
  T tree[4 * SZ]; 
  pair<int, int> lazy[4 * SZ];
  int qt = 0;
  T merge(T a, T b) {
    return a + b;
  }
  void prop(int v, int l, int r) {
    if (lazy[v].S != 0) {
      tree[v] = (r - l + 1) * lazy[v].F;
      if (l != r) {
        if (lazy[v].S > lazy[2 * v + 1].S) {
            lazy[2 * v + 1] = make_pair(lazy[v].F, lazy[v].S);
        }
        if (lazy[v].S > lazy[2 * v + 2].S) {
            lazy[2 * v + 2] = make_pair(lazy[v].F, lazy[v].S);
        }
      }
      lazy[v] = make_pair(0, 0);
    }
  }
  void update(int v, int l, int r, int ql, int qr, int x) {
    prop(v, l, r);
    if (r < ql || l > qr) {
      return;
    }
    if (l >= ql && r <= qr) {
      tree[v] = (r - l + 1) * x;
      if (l != r) {
        lazy[2 * v + 1] = make_pair(x, ++qt);
        lazy[2 * v + 2] = make_pair(x, ++qt);
      }
      return;
    }
    int m = (l + r) / 2;
    update(2 * v + 1, l, m, ql, qr, x);
    update(2 * v + 2, m + 1, r, ql, qr, x);
    tree[v] = merge(tree[2 * v + 1], tree[2 * v + 2]);
  }

  T query(int v, int l, int r, int ql, int qr) {
    prop(v, l, r);
    if (l > qr || r < ql) {
      return 0;
    }
    if (l >= ql && r <= qr) {
      return tree[v];
    } else {
      int m = (l + r) / 2;
      T a = query(2 * v + 1, l, m, ql, qr);
      T b = query(2 * v + 2, m + 1, r, ql, qr);
      return merge(a, b);
    }
  }
};

BIT<int, MX> orz;
LazySeg<int, MX> prevs;

void Solve1() {
    FOR(i, n) cin >> vals[i];
    FOR(i, q) {
        int l, r; cin >> l >> r;
        l--, r--;
        vector<pair<int, int>> locs;
        vector<bool> used(n);
        F0R(j, l, r + 1) {
            locs.push_back(make_pair(vals[j], j));
        }
        DSU<5005> dsu;
        dsu.init();
        int ccs = 0;
        ll ans = 0;
        sort(locs.begin(), locs.end());
        reverse(locs.begin(), locs.end());
        FOR(j, locs.size()) {
            int x = locs[j].S;
            int num = 0;
            used[x] = true; 
            if (x > 0 && used[x - 1]) {
                if (dsu.gmn(x - 1) == locs[j].F) {
                    ++num;
                }
                dsu.merge(x, x - 1);
            }
            if (x < n && used[x + 1]) {
                if (dsu.gmn(x + 1) == locs[j].F) {
                    ++num;
                }
                dsu.merge(x, x + 1);
            }
            if (num == 2) --ccs;
            else if (num == 0) ++ccs;
            if (j == locs.size() - 1 || locs[j + 1].F != locs[j].F) {
                ans += ccs;
                ccs = 0;
            }
        }
        cout << ans << '\n';
    }
}

void Solve2() {
    FOR(i, n) {
        cin >> vals[i];
    }
    FOR(i, q) {
        int l, r; cin >> l >> r;
        l--, r--;
        qrs[r].push_back(make_pair(l, i));
    }
    prevs.update(0, 0, n - 1, 0, n - 1, -1);
    FOR(j, n) {
        if (vals[j] != n) prevs.update(0, 0, n - 1, vals[j], n - 1, -1);
        int pos = prevs.query(0, 0, n - 1, vals[j] - 1, vals[j] - 1);
        if (pos != -1) {
            orz.upd(pos, -1);
        }
        prevs.update(0, 0, n - 1, vals[j] - 1, vals[j] - 1, j);
        orz.upd(j, 1);
        for (auto x : qrs[j]) {
            res[x.S] += orz.query(x.F, j);
        }
    }
    FOR(i, q) {
        cout << res[i] << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);    
    cin >> n >> q;
    Solve2();
}

