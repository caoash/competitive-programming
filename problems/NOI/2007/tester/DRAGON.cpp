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

const int MX = 305;

int n, m, k; 
vector<pair<int, int>> adj[MX];
int st[MX], sz[MX], ord[MX];
int dp[MX][MX][MX];
int best[MX][MX];
int cnt = 0;
int num[MX];
vector<int> vals[MX];

void dfs(int v, int p) {
    ord[cnt] = v;
    st[v] = cnt++;
    sz[v] = 1;
    for (auto to : adj[v]) {
        if (to.F != p) {
            num[to.F] = to.S;
            dfs(to.F, v);
            sz[v] += sz[to.F];
        }
    }
}

void dfs_merg(int v, int p) {
    for (auto to : adj[v]) {
        if (to.F != p) {
            dfs_merg(to.F, v); 
            for (auto x : vals[to.F]) vals[v].push_back(x); 
        }
    }
    sort(vals[v].begin(), vals[v].end());
    int sum = 0;
    FOR(i, vals[v].size()) {
        best[v][i] = sum;
        sum += vals[v][i];
    }
    best[v][vals[v].size()] = sum;
    if (v != 0) vals[v].push_back(num[v]);
}

void Solve() {
    cin >> n >> m >> k;
    { // reset
        cnt = 0;
        FOR(i, n) adj[i].clear(), st[i] = 0, vals[i].clear(), num[i] = 0, sz[i] = 0;
        FOR(i, n) FOR(j, n) best[i][j] = -1;
        FOR(i, n + 1) FOR(j, m + 1) FOR(l, k + 1) dp[i][j][l] = 1e9;
    }
    FOR(i, n - 1) {
        int u, v, w; cin >> u >> v >> w;
        u--, v--;
        adj[u].push_back({v, w}), adj[v].push_back({u, w});
    }
    dfs(0, -1);
    dfs_merg(0, -1);
    dp[0][0][0] = 0;
    FOR(i, n) dbg(i, ord[i]);
    FOR(i, n) FOR(j, m + 1) FOR(l, k + 1) {
        if (i + 1 <= n) dp[i + 1][j][l] = min(dp[i + 1][j][l], dp[i][j][l]); 
        if (i + sz[ord[i]] <= n && l + sz[i] <= (n - k)) {
            FOR(moves, m + 1) {
                if (best[i][moves] != -1 && j + moves + 1 <= m) {
                    dp[i + sz[ord[i]]][j + moves + 1][l + sz[ord[i]]] = min(dp[i + sz[ord[i]]][j + moves + 1][l + sz[ord[i]]], dp[i][j][l] + num[ord[i]] + best[ord[i]][moves]); 
                }
            }
        }
    }
    FOR(i, n + 1) FOR(j, m + 1) FOR(l, k + 1) dbg(i, j, l, dp[i][j][l]);
    cout << dp[n][m - 1][n - k] << '\n';
}

int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T; cin >> T;
    while (T--) {
        Solve();
    }
}

