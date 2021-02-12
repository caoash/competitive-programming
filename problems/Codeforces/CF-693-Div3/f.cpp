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

const int MX = 200005;

vector<int> adj[MX];
// vector<int> rev[MX];
vector<int> good[MX];
// vector<int> bad[MX];
int dist[MX], best[MX];
int val[MX];
bool vis[MX];

void Solve() {
    int n, m; cin >> n >> m;
    FOR(i, n) {
        adj[i].clear();
        good[i].clear();
    }
    vector<pair<int, int>> ed;
    FOR(i, m) {
        int u, v; cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        ed.push_back({u, v});
    }
    queue<int> bfs;
    FOR(i, n) dist[i] = 1e9, best[i] = 1e9, val[i] = 1e9, vis[i] = false;
    dist[0] = 0;
    bfs.push(0);
    while (!bfs.empty()) {
        int fr = bfs.front();
        bfs.pop();
        if (!vis[fr]) {
            for (auto to : adj[fr]) {
                if (!vis[to] && dist[to] > dist[fr] + 1) {
                    dist[to] = dist[fr] + 1;
                    bfs.push(to);
                }
            }
        }
        vis[fr] = true;
    }
    FOR(i, n) {
        val[i] = dist[i];
        for (auto to : adj[i]) {
            if (dist[to] <= dist[i]) val[i] = min(val[i], dist[to]);
        }
        best[i] = val[i];
    }
    for (auto e : ed) {
        if (dist[e.F] < dist[e.S]) {
            good[e.S].push_back(e.F);
        }
    }
    queue<pair<int, int>> sp;
    FOR(i, n) {
        sp.push({i, val[i]});
    }
    while (!sp.empty()) {
        auto fr = sp.front();
        sp.pop();
        for (auto to : good[fr.F]) {
            if (fr.S < best[to]) {
                best[to] = fr.S;
                sp.push({to, fr.S});
            }
        }
    }
    FOR(i, n) cout << best[i] << " ";
    cout << '\n';
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

