#include <bits/stdc++.h> 
using namespace std;

using ll = long long;
using ld = long double;

using vi = vector<int>;
using vl = vector<ll>;
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define lb lower_bound
#define ub upper_bound

using pi = pair<int,int>;
using pd = pair<ld, ld>;
#define f first
#define s second
#define mp make_pair

const int MX = 200005;
const int MOD = (int) (1e9 + 7);
const ll INF = (ll) 1e18;

template < int SZ > struct DSU {
  int p[SZ], sz[SZ];
  void init() {
    for (int i = 0; i < SZ; i++) {
      p[i] = i;
      sz[i] = 1;
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
    }
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
    vector<pd> pts(n);
    for (int i = 0; i < n; i++) {
        cin >> pts[i].f >> pts[i].s; 
    }
    auto dist = [&] (pd a, pd b) {
        return sqrt((b.f - a.f) * (b.f - a.f) + (b.s - a.s) * (b.s - a.s));
    };
    vector<pair<ld, pi>> edges;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            edges.pb(mp(dist(pts[i], pts[j]) / 2.0, mp(i, j))); 
        }
    }
    sort(all(edges));
    orz.init();
    ld ans = 0;
    for (auto x : edges) {
        if (orz.find(x.s.f) != orz.find(x.s.s)) {
            orz.merge(x.s.f, x.s.s);
            ans = max(ans, x.f);
        } 
    }
    cout << setprecision(12) << ans << '\n';
}

