/*
 * Unintended solution. First, condense into SCC graph.
 *
 * Then, make some observations:
 * - If two nodes are on the same "layer" of topological sort, they can't reach each other.
 * - Otherwise, a node can reach all other nodes in later layers if it's the only node in it's layer, because all later nodes must come from this node.
 *    - (makes more sense if you think about the topological sort algorithm where you remove nodes with degree 0)
 * - If there exists some node v that appears on earlier layers than a node u, then u cannot reach v. Otherwise if u is in it's own layer and no node appears later, it can visit all.
 * - First count how many nodes are in each layer of toposort, and then use that to check if a node is in a layer with another node.
 * - Then, to check if there exists some node that appears earlier in both the toposort and toposort of reverse graph, count inversions using BIT.
 */

#include <bits/stdc++.h> 
using namespace std;

using ll = long long;

using vi = vector<int>;
using vl = vector<ll>;
#define pb push_back
#define rsz resize
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using pi = pair<int,int>;
#define f first
#define s second
#define mp make_pair

const int MX = 500005;
const int MOD = (int) (1e9 + 7);
const ll INF = (ll) 1e18;

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
    pr("{", x.f, ", ", x.s, "}");
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

#ifdef LOCAL
using namespace output;
#endif

template <class T, int ...Ns> struct BIT {
    T val = 0;
    void upd(T v) { val += v; }
    T query() { return val; }
};

template <class T, int N, int... Ns> struct BIT<T, N, Ns...> {
    BIT<T,Ns...> bit[N + 1];
    template<typename... Args> void upd(int pos, Args... args) {
        for (; pos <= N; pos += (pos&-pos)) bit[pos].upd(args...);
    }
    template<typename... Args> T sum(int r, Args... args) {
        T res = 0; for (; r; r -= (r&-r)) res += bit[r].query(args...); 
        return res;
    }
    template<typename... Args> T query(int l, int r, Args... args) {
        return sum(r,args...)-sum(l-1,args...);
    }
};

vi G[MX][2];
set<int> SG[MX][2];
bool good[MX][2];
int deg[MX][2];
int scc_num[MX];
bool vis[MX];
bool ok[MX];
vi order;
vector<pi> ed;
BIT<int, MX> b;
vi topo[2];

void conn(int v) {
    vis[v] = true;
    for (int to : G[v][0]) {
        if (!vis[to]) {
            conn(to);
        }
    }
    for (int to : G[v][1]) {
        if (!vis[to]) {
            conn(to);
        }
    }
}

void dfs1(int v) {
    vis[v] = true;
    for (int to : G[v][0]) {
        if (!vis[to]) {
            dfs1(to);
        }
    }
    order.pb(v);
}

int cnt = 0;

void dfs2(int v) {
    vis[v] = true;
    scc_num[v] = cnt;
    for (int to : G[v][1]) {
        if (!vis[to]) {
            dfs2(to);
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m; cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--, v--;
        G[u][0].pb(v), G[v][1].pb(u);
        ed.pb(mp(u, v));
    }
    memset(vis, false, sizeof(vis));
    cnt = 0;
    order.clear();
    memset(vis, false, sizeof(vis));
    for (int i = 0; i < n; i++) {
        if (!vis[i]) dfs1(i);
    }
    reverse(all(order));
    memset(vis, false, sizeof(vis));
    for (int i = 0; i < n; i++) {
        int c = order[i];
        if (!vis[c]) {
            dfs2(c);
            ++cnt;
        }
    }
    memset(ok, true, sizeof(ok));
    auto Go = [&] (int v) {
        for (auto &x : ed) {
            int u = scc_num[x.f];
            int w = scc_num[x.s];
            if (v) {
                if (u != w) {
                    if (!SG[w][v].count(u)) deg[u][v]++;
                    SG[w][v].insert(u);
                }
            }
            else {
                if (u != w) {
                    if (!SG[u][v].count(w)) deg[w][v]++;
                    SG[u][v].insert(w);
                }
            }
        }
        queue<pi> fr;
        for (int i = 0; i < cnt; i++) {
            if (deg[i][v] == 0) {
                fr.push(mp(i, 0));
            }
        }
        map<int, int> col;
        vector<pi> done;
        while (!fr.empty()) {
            pi curr = fr.front(); 
            fr.pop();
            col[curr.s]++;
            topo[v].pb(curr.f);
            done.pb(curr);
            for (int to : SG[curr.f][v]) {
                deg[to][v]--;
                if (deg[to][v] == 0) {
                    fr.push(mp(to, curr.s + 1)); 
                }
            }
        }
        for (auto x : done) {
            if (col[x.s] > 1) {
                ok[x.f] = false;
            }
        }
    };
    Go(0);
    Go(1);
    map<int, int> loc;
    for (int i = 0; i < sz(topo[0]); i++) {
        loc[topo[0][i]] = i;
    }
    vi fin(n);
    for (int i = 0; i < sz(topo[1]); i++) {
        b.upd(loc[topo[1][i]] + 1, 1);
        if (i != 0) {
            fin[topo[1][i]] = b.query(1, loc[topo[1][i]]);
        }
    }
    vi ret;
    for (int i = 0; i < n; i++) {
        if (ok[scc_num[i]] && fin[scc_num[i]] == 0) ret.pb(i + 1);
    }
    cout << sz(ret) << '\n';
    for (auto x : ret) cout << x << " ";
}

