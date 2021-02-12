#include <bits/stdc++.h> 
using namespace std;

typedef long long ll;

#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)

#define F first
#define S second

const int MX = 3000005;

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
  // #define dbg(x...) pr("[", #x, "] = ["), pc(x);
}

#ifdef mikey 
using namespace output;
#else
using namespace output;
// #define dbg(x...)
#endif

int n, k;
int dp[MX];
vector<int> adj[MX];
bool marked[MX];
int cnt[MX];
int deg[MX];
int ans = -1;
int root = 0;
int placed = 0;
vector<int> res;

void dfs_mark(int v, int p, int r) {
    if (deg[v] == 1) dp[v] = 0;
    for (int to : adj[v]) {
        if (to != p) {
            // // dbg(v, to);
            dfs_mark(to, v, r);
            dp[v] = max(dp[v], dp[to] + 1);
        }
    }
    // dbg(v, r, dp[v]);
    if (dp[v] == r) {
        dp[v] = -1e9;
        ++placed;
        // // dbg("MARKING", v);
        marked[v] = true;
    }
}

void dfs_prop(int v, int p) {
    for (int to : adj[v]) {
        if (to != p) {
            dfs_prop(to, v);
            if (marked[to]) marked[v] = true;
        }
    }
}

void dfs_degs(int v, int p) {
    for (int to : adj[v]) {
        if (to != p) {
            dfs_degs(to, v);
        }
    }
    for (int to : adj[v]) cnt[v] += marked[to];
}

void dfs_ans(int v, int p, bool stor) {
    for (int to : adj[v]) {
        if (to != p) {
            dfs_ans(to, v, stor);
        }
    }
    // dbg(v, marked[v], cnt[v]);
    bool ok = (marked[v] && cnt[v] == 1);
    if (ok) {
        ++ans;
        if (stor) res.push_back(v);
    }
}

void tri(int r, bool stor) {
    ans = 0;
    placed = 0;
    FOR(i, n) marked[i] = false, dp[i] = -1e9, cnt[i] = 0;
    dfs_mark(root, -1, r);
    FOR(i, n) {
        if (placed < 2 && !marked[i]) {
            marked[i] = true, ++placed;
        }
    }
    dfs_prop(root, -1);
    dfs_degs(root, -1);
    dfs_ans(root, -1, stor);
    return;
}

int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> k;
    FOR(i, n - 1) {
        int u, v; cin >> u >> v;
        u--, v--;
        adj[u].push_back(v), adj[v].push_back(u);
        // // dbg(u, v);
        deg[u]++, deg[v]++;
    }
    while (deg[root] == 1) ++root;
    // dbg(root);
    int lo = 0, hi = n;
    int best = -1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        tri(mid, false);
        // dbg(mid, res, ans);
        // res.clear();
        if (ans <= k) {
            hi = mid - 1;
            best = mid;
        } else {
            lo = mid + 1;
        }
    }
    tri(best, true);
    cout << best << " " << ans << '\n';
    for (auto x : res) cout << x + 1 << " ";
}

