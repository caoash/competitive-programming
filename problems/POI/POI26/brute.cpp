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
    // cout << x;
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

// !x[i] => x[i + 1], !x[i + 1] => x[i] for all i
// !x[0] => x[0], !x[n - 1] => x[n - 1]
// x[i] => y[i], y[i] => y[nxt[i]], y[i] => !x[nxt[i]]

const int MX = 200005;

map<pair<int, int>, vector<pair<int, int>>> adj;
map<pair<int, int>, vector<pair<int, int>>> rev;
vector<pair<int, int>> ord;
set<pair<int, int>> vis;
map<pair<int, int>, int> scc;

void dfs1(pair<int, int> v) {
    vis.insert(v);
    for (auto to : adj[v]) {
        if (!vis.count(to)) {
            dfs1(to);
        }
    }
    ord.push_back(v);
}

void dfs2(pair<int, int> v, int c) {
    dbg(v, c);
    scc[v] = c;
    for (auto to : rev[v]) {
        if (!scc.count(to)) {
            dbg(to, -1);
            dfs2(to, c);
        } else {
            dbg(to, scc[to]);
        }
    }
}

void Solve() {
    int n, k; cin >> n >> k;
    vector<int> a(n);
    vector<int> nxt(n, -1);
    FOR(i, n) cin >> a[i];
    map<pair<int, int>, int> loc;
    FOR(i, n - 1) {
        if (loc.count(make_pair(a[i], a[i + 1]))) {
            nxt[loc[make_pair(a[i], a[i + 1])]] = i;
        }
        loc[make_pair(a[i], a[i + 1])] = i; 
    }
    FOR(i, n - 2) {
        adj[make_pair(i, 0)].push_back(make_pair(i + 1, 1));
        rev[make_pair(i + 1, 1)].push_back(make_pair(i, 0));
        // cout << i << ",0 " << i + 1 << ",1" << '\n';
        adj[make_pair(i + 1, 0)].push_back(make_pair(i, 1));
        rev[make_pair(i, 1)].push_back(make_pair(i + 1, 0));
        // cout << i + 1 << ",0 " << i << ",1" << '\n';
    }
    adj[make_pair(0, 0)].push_back(make_pair(0, 1));
    rev[make_pair(0, 1)].push_back(make_pair(0, 0));
    // cout << "0,0 0,1" << '\n';
    adj[make_pair(n - 2, 0)].push_back(make_pair(n - 2, 1));
    rev[make_pair(n - 2, 1)].push_back(make_pair(n - 2, 0));
    // cout << n-2 << ",0 " << n - 2 << ",1" << '\n';
    FOR(i, n - 1) {
        adj[make_pair(i, 1)].push_back(make_pair(i, 3));
        adj[make_pair(i, 2)].push_back(make_pair(i, 0));
        rev[make_pair(i, 3)].push_back(make_pair(i, 1));
        rev[make_pair(i, 0)].push_back(make_pair(i, 2));
        // cout << i << ",1 " << i << ",3" << '\n';
        if (nxt[i] != -1) {
            adj[make_pair(i, 3)].push_back(make_pair(nxt[i], 3));
            adj[make_pair(nxt[i], 2)].push_back(make_pair(i, 2));
            rev[make_pair(nxt[i], 3)].push_back(make_pair(i, 3));
            rev[make_pair(i, 2)].push_back(make_pair(nxt[i], 2));
            // cout << i << ",3 " << nxt[i] << ",3" << '\n';
            adj[make_pair(i, 3)].push_back(make_pair(nxt[i], 0));
            adj[make_pair(nxt[i], 1)].push_back(make_pair(i, 2));
            rev[make_pair(nxt[i], 0)].push_back(make_pair(i, 3));
            rev[make_pair(i, 2)].push_back(make_pair(nxt[i], 1));
            // cout << i << ",3 " << nxt[i] << ",0" << '\n';
        }
    }
    ord.clear();
    vis.clear();
    scc.clear();
    FOR(i, n - 1) {
        FOR(j, 4) {
            if (!vis.count(make_pair(i, j))) {
                dfs1(make_pair(i, j));
            }
        }
    }
    dbg(ord);
    // // dbg(ord);
    int cnt = 0;
    FOR(i, ord.size()) {
        pair<int, int> v = ord[ord.size() - i - 1];
        // dbg(scc);
        if (!scc.count(v)) {
            dfs2(v, cnt++);
        }
    }
    FOR(i, n - 1) {
        // dbg(i, scc[make_pair(i, 0)], scc[make_pair(i, 1)], scc[make_pair(i, 2)], scc[make_pair(i, 3)]);
        if (scc[make_pair(i, 0)] == scc[make_pair(i, 1)] || scc[make_pair(i, 2)] == scc[make_pair(i, 3)]) {
            cout << "NIE\n";
            return;
        }
    }
    cout << "TAK\n";
    return;
}
 
int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);    
    int T; cin >> T;
    while (T--) {
        rev.clear();
        adj.clear();
        Solve();
    }
}
