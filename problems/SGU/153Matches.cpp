#include <bits/stdc++.h> 
using namespace std;
 
typedef long long ll;
 
#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)
 
#define F first
#define S second

bool win[10005][2];

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

int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);    
    /*
    win[1][0] = false;
    win[1][1] = true;
    // int mask = 22;
    set<int> masks;
    FOR(mask, 256) {
        F0R(i, 2, 1000) {
            F0R(j, 1, 9) {
                if (j == 1 || mask & (1 << (j - 1))) {
                    if (!win[i - j][0]) {
                        win[i][1] = false;
                        break;
                    }
                    win[i][1] = true;
                }
            }
            F0R(j, 1, 9) {
                if (j == 1 || (mask & (1 << (j - 1)))) {
                    if (win[i - 1][1]) {
                        win[i][0] = true;
                        break;
                    }
                    win[i][0] = false;
                }
            }
            if (win[i][0] && i > 2) {
                dbg(mask, i);
                masks.insert(mask);
            }
        }
    }
    */
    int k; cin >> k;
    while (k--) {
        int n, m; cin >> n >> m;
        win[1][0] = false;
        win[1][1] = true;
        int mask = 0;
        vector<int> a(m);
        FOR(i, m) {
            cin >> a[i];
            mask |= (1 << (a[i] - 2));
        }
        F0R(i, 2, 10005) {
            F0R(j, 1, 10) {
                if (j == 1 || mask & (1 << (j - 2))) {
                    if (!win[i - j][0]) {
                        win[i][1] = false;
                        break;
                    }
                    win[i][1] = true;
                }
            }
            F0R(j, 1, 10) {
                if (j == 1 || (mask & (1 << (j - 2)))) {
                    if (win[i - j][1]) {
                        win[i][0] = true;
                        break;
                    }
                    win[i][0] = false;
                }
            }
        }
        string per = "";
        bool done = false;
        FOR(offset, 105) {
            F0R(len, 1, 105) {
                bool good = true;
                F0R(pos, offset, offset + len) {
                    F0R(test, 1, 105) {
                        if (win[pos][0] != win[pos + (len * test)][0]) {
                            good = false; 
                        }
                    }
                }
                if (good) {
                    if (n <= offset) {
                        cout << (win[n][0] ? "FIRST PLAYER MUST WIN" : "SECOND PLAYER MUST WIN") << '\n';
                    } else {
                        cout << (win[((n - offset) % len) + offset][0] ? "FIRST PLAYER MUST WIN" : "SECOND PLAYER MUST WIN") << '\n';
                    }
                    /*
                    F0R(pos, offset, offset + len) {
                        cout << (win[pos][0] ? "W" : "L");
                    }
                    */
                    done = true;
                    break;
                }
            }
            if (done) break;
        }
    }
}

