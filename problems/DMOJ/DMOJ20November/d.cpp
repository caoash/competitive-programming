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

const int MX = 50005;
const int MOD = (int) (1e9 + 7);
const ll INF = (ll) 1e18;

template < class T, int SZ > struct LazySeg {
  T tree[4 * SZ], lazy[4 * SZ];
  T merge(T a, T b) {
    return min(a, b);
  }

  void prop(int v, int l, int r) {
    if (lazy[v] != 0) {
      tree[v] += lazy[v];
      if (l != r) {
        lazy[2 * v + 1] += lazy[v];
        lazy[2 * v + 2] += lazy[v];
      }
      lazy[v] = 0;
    }
  }

  void update(int v, int l, int r, int ql, int qr, int x) {
    prop(v, l, r);
    if (r < ql || l > qr) {
      return;
    }
    if (l >= ql && r <= qr) {
      tree[v] += x;
      if (l != r) {
        lazy[2 * v + 1] += x;
        lazy[2 * v + 2] += x;
      }
      return;
    }
    int m = (l + r) / 2;
    update(2 * v + 1, l, m, ql, qr, x);
    update(2 * v + 2, m + 1, r, ql, qr, x);
    tree[v] = merge(tree[2 * v + 1], tree[2 * v + 2]);
  }

  T query(int v, int l, int r, int ql, int qr) {
    prop(v, l, r);
    if (l > qr || r < ql) {
      return INT_MAX;
    }
    if (l >= ql && r <= qr) {
      return tree[v];
    } else {
      int m = (l + r) / 2;
      T a = query(2 * v + 1, l, m, ql, qr);
      T b = query(2 * v + 2, m + 1, r, ql, qr);
      return merge(a, b);
    }
  }
};

LazySeg<int, MX> orz;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m; cin >> n >> m;
    vi b(n), d(m);
    for (int i = 0; i < n; i++) cin >> b[i];
    for (int i = 0; i < n; i++) orz.update(0, 0, n - 1, i, n - 1, -1);
    sort(all(b));
    int ans = 0;
    for (int i = 0; i < m; i++) {
        cin >> d[i];
        int f = upper_bound(all(b), d[i]) - b.begin(); 
        orz.update(0, 0, n - 1, f, n - 1, 1);
        if (orz.query(0, 0, n - 1, 0, n - 1) == 0) {
            ++ans;
            for (int j = 0; j < n; j++) {
                orz.update(0, 0, n - 1, j, n - 1, -1);
            }
        }
        cout << ans << " ";
    }
}
