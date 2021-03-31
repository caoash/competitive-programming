#include <bits/stdc++.h> 
using namespace std;
 
typedef long long ll;
 
#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)
 
#define F first
#define S second
// #define int ll

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

pair<int, int> day[200005];
int dp[200005][2], pre[200005][2];

signed main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);    
    int n; cin >> n;
    vector<pair<int, int>> vals(n + 1);
    vals[0] = make_pair(0, 0);
    FOR(i, n) cin >> vals[i + 1].S >> vals[i + 1].F;
    vector<pair<int, char>> ans;
    bool bad = false;
    auto sim = [&] (int i, pair<int, int> &a, pair<int, int> &b) {
        int len = b.S - a.S;
        int at = a.F + len;
        if (at < b.F) {
            bad = true;
            cout << -1 << '\n';
            return;
        }
        int need = (at - b.F);
        if (need % 2) {
            bad = true;
            cout << -1 << '\n';
            return;
        }
        int down = need / 2, up = len - down;
        if (down > len || up > len) {
            bad = true;
            cout << -1 << '\n';
            return;
        }
        // dbg(a, b, down, up);
        day[i] = make_pair(up, down);
    };
    FOR(i, n) {
        if (bad) break;
        sim(i, vals[i], vals[i + 1]);
    }
    FOR(i, n) {
        // dbg(i, day[i]);
    }
    FOR(i, n + 1) dp[i][0] = 1e9, dp[i][1] = 1e9;
    dp[0][0] = 1;
    dp[0][1] = 1;
    F0R(i, 1, n + 1) {
        // dbg(i, day[i - 1]);
        if (day[i - 1].F > 0 && day[i - 1].S > 0) {
            if (dp[i - 1][0] + 1 < dp[i - 1][1] + 2) {
                dp[i][1] = dp[i - 1][0] + 1;
                pre[i][1] = 0;
            } else {
                dp[i][1] = dp[i - 1][1] + 2;
                pre[i][1] = 1;
            }
            if (dp[i - 1][1] + 1 < dp[i - 1][0] + 2) {
                dp[i][0] = dp[i - 1][1] + 1; 
                pre[i][0] = 1;
            } else {
                dp[i][0] = dp[i - 1][0] + 2;
                pre[i][0] = 0;
            }
        } else if (day[i - 1].F > 0) {
            if (dp[i - 1][0] < dp[i - 1][1] + 1) {
                dp[i][0] = dp[i - 1][0];
                pre[i][0] = 0;
            } else {
                dp[i][0] = dp[i - 1][1] + 1;
                pre[i][0] = 1;
            }
        } else if (day[i - 1].S > 0) {
            if (dp[i - 1][0] + 1 < dp[i - 1][1]) {
                dp[i][1] = dp[i - 1][0] + 1;
                pre[i][1] = 0;
            } else {
                dp[i][1] = dp[i - 1][1];
                pre[i][1] = 1;
            }
        }
        // dbg(i, dp[i][0], dp[i][1]);
    }
    int pos = n, best = 0;
    if (dp[pos][1] < dp[pos][0]) best = 1;
    while (pos > 0) {
        if (best == 0) {
            if (day[pos - 1].F) ans.push_back(make_pair(day[pos - 1].F, '+'));
            if (day[pos - 1].S) ans.push_back(make_pair(day[pos - 1].S, '-'));
        } else {
            if (day[pos - 1].S) ans.push_back(make_pair(day[pos - 1].S, '-'));
            if (day[pos - 1].F) ans.push_back(make_pair(day[pos - 1].F, '+'));
        }
        best = pre[pos][best];
        pos--;
    }
    vector<pair<int, char>> fin;
    char cur = '$';
    int sum = 0;
    while (!ans.empty()) {
        if (ans.back().S == cur) {
            sum += ans.back().F; 
        } else {
            if (cur != '$') fin.push_back(make_pair(sum, cur));
            cur = ans.back().S;
            sum = ans.back().F;
        }
        ans.pop_back();
    }
    if (sum) fin.push_back(make_pair(sum, cur));
    // // FOR(i, n) dbg(i, day[i]);
    if (!bad) {
        cout << fin.size() << '\n';
        for (auto x : fin) cout << x.F << " " << x.S << '\n';
    }
}

