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

const int MX = 1005;

int n, a, b;
vector<int> adj[2 * MX][2];
int leaf[MX][2];
int pos[2 * MX][2];
int siz[2 * MX][2];
int best[MX][MX][2];
int ans[MX][2];
pair<int, int> rang[2 * MX][2];

void dfs(int v, int p, int d) {
    if (pos[v][d] != -1) rang[v][d] = {pos[v][d], pos[v][d]};
    siz[v][d] = 1;
    dbg(v, d, adj[v][d]);
    for (int to : adj[v][d]) {
        if (to != p) {
            dfs(to, v, d);
            siz[v][d] += siz[to][d];
            rang[v][d].F = min(rang[v][d].F, rang[to][d].F);
            rang[v][d].S = max(rang[v][d].S, rang[to][d].S);
        }
    }
}

int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> a;
    FOR(i, a) pos[i][0] = -1, rang[i][0] = {1e9, -1e9};
    FOR(i, a - 1) {
        int p; cin >> p;
        adj[p - 1][0].push_back(i + 1);
    }
    FOR(i, n) {
        cin >> leaf[i][0], leaf[i][0]--;
        pos[leaf[i][0]][0] = i;
    }
    cin >> b;
    FOR(i, b) pos[i][1] = -1, rang[i][1] = {1e9, -1e9};
    FOR(i, b - 1) {
        int p; cin >> p;
        dbg(p - 1, i + 1);
        adj[p - 1][1].push_back(i + 1);
    }
    FOR(i, n) {
        cin >> leaf[i][1], leaf[i][1]--;
        pos[leaf[i][1]][1] = i;
    }
    dfs(0, -1, 0);
    dfs(0, -1, 1);
    FOR(i, a) {
        auto cur = rang[i][0];
        best[cur.F][cur.S][0] = max(best[cur.F][cur.S][0], siz[i][0] - (i == 0));
    }
    FOR(i, b) {
        auto cur = rang[i][1];
        best[cur.F][cur.S][1] = max(best[cur.F][cur.S][1], siz[i][1] - (i == 0));
    }
    FOR(c, 2) {
        F0R(len, 2, n + 1) {
            FOR(st, n) {
                if (st + len < n) {
                    int l = st, r = st + len - 1;
                    if (l < r) best[l][r][c] = max(best[l][r][c], best[l + 1][r][c] + best[l][l][c]);
                    if (r > l) best[l][r][c] = max(best[l][r][c], best[l][r - 1][c] + best[r][r][c]);
                }
            }
        }
    }
    FOR(i, n + 1) ans[i][0] = -1e9, ans[i][1] = -1e9;
    ans[0][0] = 0, ans[0][1] = 0;
    F0R(i, 1, n + 1) {
        FOR(j, i) {
            ans[i][0] = max(ans[i][0], ans[j][1] + best[j][i - 1][1]); 
            ans[i][1] = max(ans[i][1], ans[j][0] + best[j][i - 1][0]); 
        }
    }
    FOR(i, n) F0R(j, i, n) dbg(i, j, best[i][j][0], best[i][j][1]);
    cout << max(ans[n][0], ans[n][1]) << '\n';
}

