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

ll dat[MX];
vi adj[MX];

template < int SZ > struct DSU {
  int p[SZ], sz[SZ], mx[SZ];
  void init() {
    for (int i = 0; i < SZ; i++) {
      p[i] = i;
      sz[i] = 1;
      mx[i] = dat[i];
    }
  }
  int find(int x) {
    return p[x] = (p[x] == x ? x : find(p[x]));
  }
  void merge(int u, int v) {
    int a = find(u);
    int b = find(v);
    if (a != b) {
      if (sz[a] < sz[b]) {
        swap(a, b);
      }
      p[b] = a;
      sz[a] += sz[b];
      mx[a] = max(mx[a], mx[b]);
    }
  }
  int gmx(int u) {
    return mx[find(u)];
  }
};

DSU<MX> orz;

int main(){
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    for (int i = 0; i < n; i++) cin >> dat[i];
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        u--, v--;
        if (dat[v] > dat[u]) swap(u, v);
        adj[u].pb(v);
    }
    vi nums(n);
    iota(all(nums), 0);
    sort(all(nums), [&] (int i, int j) {
        return dat[i] < dat[j];
    });
    orz.init();
    ll ans = 0;
    for (auto x : nums) {
        for (int to : adj[x]) {
            ans += orz.gmx(x) + orz.gmx(to);
            orz.merge(x, to);
        }
    }
    cout << ans << '\n';
}

