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

DSU<MX> dsu;

vector<pair<int, pi>> ed;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int m, n; cin >> m >> n;
    vi a(m), b(n);
    for (int i = 0; i < m; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];
    ll ans = 0;
    for (int i = 0; i < m; i++) {
        int x; cin >> x;
        for (int j = 0; j < x; j++) {
            int v; cin >> v;
            ed.pb(mp(a[i] + b[v - 1], mp(i + n, v - 1)));
            ans += (a[i] + b[v - 1]);
        }
    }
    dsu.init();
    sort(all(ed));
    reverse(all(ed));
    for (auto &x : ed) {
        if (dsu.find(x.s.f) != dsu.find(x.s.s)) {
            dsu.merge(x.s.f, x.s.s);
            ans -= x.f;
        }
    }
    cout << ans << '\n';
}

