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

const int MX = 1000005;

int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);    
    string a, b; cin >> a >> b;
    int n = a.size(), m = b.size();
    string alph = "ACGT";
    auto tri = [&] (string &at, int v) {
        char c = alph[v];
        dbg(at, c);
        vector<int> best_a(n), best_b(m);
        vector<vector<int>> nxt_a(n), nxt_b(m);
        FOR(i, n) nxt_a[i].resize(4);
        FOR(i, m) nxt_b[i].resize(4);
        FORD(i, n) {
            int pre = (i == n - 1 ? 0 : best_a[i + 1]);
            if (a[i] == at[at.size() - pre - 1]) {
                best_a[i] = pre + 1;
            } else {
                best_a[i] = pre;
            }
            FOR(j, 4) {
                if (a[i] == alph[j]) {
                    nxt_a[i][j] = i;
                } else {
                    if (i != n - 1) nxt_a[i][j] = nxt_a[i + 1][j];
                    else nxt_a[i][j] = n;
                }
            }
        }
        FORD(i, m) {
            int pre = (i == m - 1 ? 0 : best_b[i + 1]);
            if (b[i] == at[at.size() - pre - 1]) {
                best_b[i] = pre + 1;
            } else {
                best_b[i] = pre;
            }
            FOR(j, 4) {
                if (b[i] == alph[j]) {
                    nxt_b[i][j] = i;
                } else {
                    if (i != m - 1) nxt_b[i][j] = nxt_b[i + 1][j];
                    else nxt_b[i][j] = m;
                }
            }
        }
        vector<int> occ_a, occ_b;
        FOR(i, n) if (a[i] == c) occ_a.push_back(i);
        FOR(i, m) if (b[i] == c) occ_b.push_back(i);
        string res = "";
        int p1 = -1, p2 = -1;
        int rem = at.size();
        int i = 0, j = 0;
        while (i < occ_a.size() && j < occ_b.size()) {
            while (i < occ_a.size() && occ_a[i] < p1) {
                ++i;
            }
            while (j < occ_b.size() && occ_b[j] < p2) {
                ++j;
            }
            if (i >= occ_a.size() || j >= occ_b.size()) break;
            if (best_a[occ_a[i]] >= rem && best_b[occ_b[j]] >= rem) {
                res += c;
                p1 = occ_a[i], p2 = occ_b[j]; 
                i++, j++;
            } else {
                while (rem > 0 && (best_a[occ_a[i]] < rem || best_b[occ_b[j]] < rem)) {
                    char go = at[at.size() - rem];
                    res += go;
                    --rem;
                    FOR(k, 4) {
                        if (alph[k] == go) {
                            p1 = nxt_a[p1 + 1][k];
                            p2 = nxt_b[p2 + 1][k];
                            break;
                        }
                    }
                }
                while (i < occ_a.size() && occ_a[i] < p1) {
                    ++i;
                }
                while (j < occ_b.size() && occ_b[j] < p2) {
                    ++j;
                }
                if (i >= occ_a.size() || j >= occ_b.size()) break;
                if (best_a[occ_a[i]] >= rem && best_b[occ_b[j]] >= rem) {
                    res += c;
                    p1 = occ_a[i], p2 = occ_b[j]; 
                    i++, j++;
                }
            }
        }
        while (rem > 0) {
            res += at[at.size() - rem];
            --rem;
        }
        dbg(res);
        return res;
    };
    string ans = "";
    FOR(i, 4) {
        ans = tri(ans, i);
    }
    cout << ans << '\n';
}

