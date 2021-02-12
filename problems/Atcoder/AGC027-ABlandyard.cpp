#include <bits/stdc++.h> 
using namespace std;

using ll = long long;

using vi = vector<int>;
using vl = vector<ll>;
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define lb lower_bound
#define ub upper_bound

using pi = pair<int,int>;
#define f first
#define s second
#define mp make_pair

const int MX = 200005;
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

#ifdef mikey 
using namespace output;
#else
using namespace output;
#define dbg(x...)
#endif

int n, m;
string s;
vector<pi> adj[MX][6];
bool vis[MX][6];
vector<pi> eds;

bool solve(string chk) {
    memset(vis, false, sizeof(vis));
    for (int i = 0; i < n; i++) for (int j = 0; j < 6; j++) adj[i][j].clear(); 
    for (int lay = 0; lay < 5; lay++) {
        for (auto x : eds) {
            if (s[x.f] == chk[lay] && s[x.s] == chk[lay + 1]) {
                adj[x.f][lay].pb(mp(x.s, lay + 1));
            }
        }
    }
    queue<pi> bfs;
    for (int i = 0; i < n; i++) {
        if (s[i] == chk[0]) bfs.push(mp(i, 0));
    }
    while (!bfs.empty()) {
        pi curr = bfs.front();
        bfs.pop();
        for (auto to : adj[curr.f][curr.s]) {
            if (!vis[to.f][to.s]) {
                bfs.push(mp(to.f, to.s));
            }
        }
        vis[curr.f][curr.s] = true;
    }
    for (int i = 0; i < n; i++) {
        if (s[i] == chk[5] && vis[i][5]) return true;
    }
    return false;
}

int main(){
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    cin >> s;
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--, v--;
        eds.pb(mp(u, v)), eds.pb(mp(v, u));
    }
    bool ans = true;
    vector<string> poss = {"AA", "BB", "A", "B"};
    do {
        string res = "";
        for (auto x : poss) res += x;
        ans &= solve(res);
    } while (next_permutation(all(poss)));
    cout << (ans ? "Yes" : "No") << '\n';
}

