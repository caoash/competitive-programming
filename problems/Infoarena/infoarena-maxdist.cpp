

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

template < int SZ > struct LCA {
  int depth[SZ];
  int p[SZ][33];
  vector < int > adj[SZ];
  void addEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  void dfs(int v, int par) {
    for (int to: adj[v]) {
      if (to != par) {
        p[to][0] = v;
        depth[to] = depth[v] + 1;
        dfs(to, v);
      }
    }
  }
  void precomp() {
    for (int i = 0; i < SZ; i++) {
      for (int j = 0; j < 32; j++) {
        p[i][j] = -1;
      }
    }
    p[0][0] = 0;
    dfs(0, -1);
    for (int j = 1; j < 32; j++) {
      for (int i = 0; i < SZ; i++) {
        if (p[i][j - 1] == -1) {
          p[i][j] = -1;
        } else {
          p[i][j] = p[p[i][j - 1]][j - 1];
        }
      }
    }
  }
  int query(int a, int b) {
    if (depth[a] > depth[b]) {
      swap(a, b);
    }
    int lift = depth[b] - depth[a];
    for (int j = 31; j >= 0; j--) {
      if (lift & (1 << j)) {
        b = p[b][j];
      }
    }
    for (int j = 31; j >= 0; j--) {
      if (p[a][j] != p[b][j]) {
        a = p[a][j];
        b = p[b][j];
      }
    }
    return (a == b) ? a : p[a][0];
  }
};

int n;
vi adj[MX];
int sol[MX][2];
int dep[MX];
LCA<MX> anc;

int dist(int u, int v) {
    int lca = anc.query(u, v);
    int ans = anc.depth[u] + anc.depth[v];
    ans -= 2 * anc.depth[lca];
    return ans;
}

void solve(vi upds, int t) {
    pi diam = mp(-1, -1);
    int cdist = -1;
    for (int i = 0; i < sz(upds); i++) {
        int x = upds[i];
        if (diam.f == -1) {
            diam = mp(x, x);
            cdist = 0;
        } else {
            int d1 = dist(x, diam.f);
            int d2 = dist(x, diam.s);
            if (d1 > cdist && d2 > cdist) {
                if (d1 > d2) {
                    cdist = d1;
                    diam = mp(x, diam.f);
                } else {
                    cdist = d2;
                    diam = mp(x, diam.s);
                }
            } else if (d1 > cdist) {
                cdist = d1;
                diam = mp(x, diam.f);
            } else if (d2 > cdist) {
                cdist = d2;
                diam = mp(x, diam.s);
            }
        }
        sol[i][t] = cdist;
    }
}

int main(){
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    freopen("maxdist.in", "r", stdin);
    freopen("maxdist.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    int q; cin >> n >> q;
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        u--, v--;
        adj[u].pb(v), adj[v].pb(u);
        anc.addEdge(u, v);
    }
    anc.precomp();
    vi ord;
    vector<bool> used(n);
    for (int i = 0; i < q; i++) {
        int x; cin >> x;
        x--;
        ord.pb(x);
        used[x] = true;
    }
    for (int i = 0; i < n; i++) if (!used[i]) ord.pb(i);
    solve(ord, 0);
    reverse(all(ord));
    solve(ord, 1);
    for (int i = 0; i < q; i++) {
        cout << sol[n - i - 2][1] << " " << sol[i][0] << '\n';
    }
}

