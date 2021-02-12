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

template < class T, int SZ > struct LazySeg {
  T tree[SZ], lazy[SZ];
  T merge(T a, T b) {
    return a + b;
  }
  void prop(int v, int l, int r) {
    if (lazy[v] != 0) {
      tree[v] *= lazy[v];
      if (l != r) {
        lazy[2 * v + 1] *= lazy[v];
        lazy[2 * v + 2] *= lazy[v];
      }
      lazy[v] = 0;
    }
  }
  void update(int v, int l, int r, int ql, int qr, int x) {
    if (r < ql || l > qr) {
      return;
    }
    prop(v, l, r);
    if (l >= ql && r <= qr) {
      tree[v] *= x;
      if (l != r) {
        lazy[2 * v + 1] *= x;
        lazy[2 * v + 2] *= x;
      }
      return;
    }
    int m = (l + r) / 2;
    update(2 * v + 1, l, m, ql, qr, x);
    update(2 * v + 2, m + 1, r, ql, qr, x);
    tree[v] = merge(tree[2 * v + 1], tree[2 * v + 2]);
  }

  T query(int v, int l, int r, int ql, int qr) {
    if (l > qr || r < ql) {
      return 0;
    }
    prop(v, l, r);
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

int main(){
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m; cin >> n >> m;
    set<string> vals;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        vals.insert(s);
    }
    for (int i = 0; i < m; i++) {
        string s; cin >> s;
        if (!vals.count(s)) cout << i + 1 << " ";
    }
    cout << '\n';
}

