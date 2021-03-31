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

vector<int> adj[MX];
int dp[MX], sub[MX];

void dfs(int v, int p) {
    sub[v] = 1;
    dp[v] = 1;
    vector<int> child;
    int bad = 0;
    for (int to : adj[v]) {
        if (to != p) {
            dfs(to, v);
            sub[v] += sub[to];
            if (sub[to] % 2 == 0 && dp[to] < 0) {
                dp[v] += dp[to];
            } else if (sub[to] % 2 == 1) {
                child.push_back(dp[to]);
            } else {
                bad += dp[to];
            }
        }
    }
    sort(child.begin(), child.end());
    FOR(i, child.size()) {
        if (i % 2 == 0) dp[v] += child[i];
        else dp[v] -= child[i];
    }
    if (child.size() % 2) {
        dp[v] -= bad; 
    } else {
        dp[v] += bad;
    }
}
 
int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);    
    int n; cin >> n;
    FOR(i, n - 1) {
        int p; cin >> p;
        adj[i + 1].push_back(p - 1);
        adj[p - 1].push_back(i + 1);
    }

    dfs(0, -1);
    cout << (n + dp[0]) / 2 << '\n';
}

