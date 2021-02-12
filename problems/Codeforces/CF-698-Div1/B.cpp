#include <bits/stdc++.h> 
using namespace std;

typedef long long ll;

#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)

#define F first
#define S second

template < class T, int SZ > struct LazySeg {
  T tree[4 * SZ], lazy[4 * SZ];
  T merge(T a, T b) {
    return a + b;
  }
  void prop(int v, int l, int r) {
    if (lazy[v] != -1) {
      tree[v] = (r - l + 1) * lazy[v];
      if (l != r) {
        lazy[2 * v + 1] = lazy[v];
        lazy[2 * v + 2] = lazy[v];
      }
      lazy[v] = -1;
    }
  }
  void update(int v, int l, int r, int ql, int qr, int x) {
    prop(v, l, r);
    if (r < ql || l > qr) {
      return;
    }
    if (l >= ql && r <= qr) {
      tree[v] = (r - l + 1) * x;
      if (l != r) {
        lazy[2 * v + 1] = x;
        lazy[2 * v + 2] = x;
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
      return 0;
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

const int MX = 200005;

LazySeg<int, MX> orz;

void Solve() {
    int n, q; cin >> n >> q;
    string s, f; cin >> s >> f;
    FOR(i, n) orz.update(0, 0, n - 1, i, i, f[i] - '0');
    bool good = true;
    vector<pair<int, int>> ops;
    FOR(i, q) {
        int l, r; cin >> l >> r;
        l--, r--;
        ops.push_back({l, r});
    }
    reverse(ops.begin(), ops.end());
    FOR(i, q) {
        int l = ops[i].F, r = ops[i].S;
        int ones = orz.query(0, 0, n - 1, l, r);
        int zeroes = (r - l + 1) - ones;
        // cout << "l, r, ones, zeroes: " << l << " " << r << " " << ones << " " << zeroes << '\n';
        if (ones == zeroes) {
            good = false;
        } else if (ones < zeroes) {
            orz.update(0, 0, n - 1, l, r, 0);
            // cout << "UPDATING: " << l << " " << r << " " << 0 << '\n';
        } else {
            orz.update(0, 0, n - 1, l, r, 1);
            // cout << "UPDATING: " << l << " " << r << " " << 1 << '\n';
        }
    }
    FOR(i, n) {
        // cout << orz.query(0, 0, n - 1, i, i);
        good &= (orz.query(0, 0, n - 1, i, i) == (s[i] - '0'));
    }
    cout << (good ? "YES" : "NO") << '\n';
}

int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T; cin >> T;
    while (T--) {
        Solve();
    }
}

