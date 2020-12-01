/*
 * If you fix the start point, then you can perform a simple greedy, but a condition must hold that nothing
 * passes (i - 1, i). You can find such a point by using DSU.
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
#define lb lower_bound
 
using pi = pair<int,int>;
#define f first
#define s second
#define mp make_pair
 
const int MX = 500005;
const int MOD = (int) (1e9 + 7);
const ll INF = (ll) 1e18;
 
template < int SZ > struct DSU {
  int p[SZ], en[SZ];
  void init() {
    for (int i = 0; i < SZ; i++) {
      p[i] = i;
      en[i] = i;
    }
  }
  int find(int x) {
    return p[x] = (p[x] == x ? x : find(p[x]));
  }
  void merge(int u, int v) {
    int a = find(u);
    int b = find(v);
    if (a != b) {
      p[b] = a;
      en[a] = en[b];
    }
  }
};
 
bool marked[MX];
DSU<MX> dsu;
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    vector<vi> a(n); 
    vi sx(n), sy(n);
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        a[x - 1].pb(i);
    }
    for (int i = 0; i < n; i++) cin >> sx[i];
    for (int i = 0; i < n; i++) cin >> sy[i];
    dsu.init();
    set<int> vals;
    auto mark = [&] (int i) {
        assert(!marked[i]);
        marked[i] = true;
        int prev = (i - 1 + n) % n;
        int nxt = (i + 1) % n;
        if (marked[prev]) {
            dsu.merge(prev, i);
        }
        if (marked[nxt]) {
            dsu.merge(i, nxt);
        }
    };
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < sz(a[i]); j++) {
            if (!marked[i]) {
                mark(i);
            } else {
                int lst = dsu.en[dsu.find(i)];
                mark((lst + 1) % n);
            }
        }
    }
    int st = (dsu.en[dsu.find(0)] + 1) % n;
    rotate(a.begin(), a.begin() + st, a.end());
    rotate(sx.begin(), sx.begin() + st, sx.end());
    set<int> dudes;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (auto x : a[i]) dudes.insert(sy[x]);
        auto it = dudes.lb(sx[i]);
        if (it == dudes.end()) {
            dudes.erase(dudes.begin());
        } else {
            ++ans;
            dudes.erase(it);
        }
    }
    cout << ans << '\n';
}
