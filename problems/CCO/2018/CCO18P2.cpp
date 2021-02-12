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

#include <bits/stdc++.h>
using namespace std;

int rand(int a, int b){
    return a + rand()%(b-a+1);
}

int n;
int a[105][105];
int dp[105][105];
double res = 0;

int SolveBad() {
    int x = 1, y = 1, sx = 0, sy = 0;
    F0R(i, 2, n + 1) {
        // dbg(i, x, y, a[x - 1][i - 1], a[y - 1][i - 1]);
        if (sx + a[x - 1][i - 1] < sy + a[y - 1][i - 1]) {
            // dbg(x - 1, i - 1, a[x - 1][i - 1]);
            sx += a[x - 1][i - 1];
            x = i;
        } else {
            // dbg(y - 1, i - 1, a[y - 1][i - 1]);
            sy += a[y - 1][i - 1];
            y = i;
        }
        dbg(i, x, y, sx, sy);
    }
    return sx + sy;
}

int SolveGood() {
    FOR(i, n + 1) FOR(j, n + 1) dp[i][j] = 1e9;
    dp[0][0] = 0;
    FOR(i, n) {
        FOR(j, n) {
            int pos = max(i, j);
            if (pos < n) {
                dp[pos + 1][j] = min(dp[pos + 1][j], dp[i][j] + a[i][pos + 1]);
                dp[i][pos + 1] = min(dp[i][pos + 1], dp[i][j] + a[j][pos + 1]);
            }
            // dbg(i, j, dp[i][j]);
        }
    }
    int ans = 1e9;
    FOR(i, n) ans = min(ans, min(dp[i][n - 1], dp[n - 1][i]));
    return ans;
}

void Run() {
    /*
    n = rand(100, 100);
    F0R(i, 1, n) {
        FOR(j, n - i) {
            int &val = a[i - 1][i + j];
            if (j == 0) {
                val = 2;
            } else {
                val = rand(1, 2);
                if (val == 2) val = 100;
            }
        }
    }
    */
    int X = SolveBad(), Y = SolveGood();
    double res = (double) ((double) X / (double) (4 * Y));
    dbg(X, Y, res);
}

int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    FOR(i, n + 1) FOR(j, n + 1) a[i][j] = 0;
    F0R(i, 1, n) {
        FOR(j, n - i) {
            cin >> a[i - 1][i + j];
        }
    }
    FOR(i, n + 1) F0R(j, i + 1, n + 1) dbg(i, j, a[i][j]);
    // cout << SolveBad() << '\n';
    // Run();
    FOR(i, 1) Run();
}

