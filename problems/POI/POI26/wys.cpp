#include <bits/stdc++.h> 
using namespace std;
 
typedef long long ll;
 
#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)
 
#define F first
#define S second

const int MX = 3e5;

template < class T, int SZ > struct LazySeg {
  T tree[4 * SZ], lazy[4 * SZ];
  T merge(T a, T b) {
    return max(a, b);
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
  void update(int v, int l, int r, int ql, int qr, ll x) {
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
      return -1e18;
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

  int lowb(int v, int l, int r, ll x) {
    prop(v, l, r);
    if (l == r) {
        if (tree[v] >= x) {
            return l;
        }
        return 1e9;
    } else {
        int m = (l + r) / 2;
        prop(2 * v + 1, l, m);
        prop(2 * v + 2, m + 1, r);
        if (tree[2 * v + 1] >= x) {
            return lowb(2 * v + 1, l, m, x);
        } else {
            return lowb(2 * v + 2, m + 1, r, x);
        }
    }
  }

  int hib(int v, int l, int r, ll x) {
    prop(v, l, r);
    if (l == r) {
        if (tree[v] > x) return l;
        return 1e9;
    } else {
        int m = (l + r) / 2;
        prop(2 * v + 1, l, m);
        prop(2 * v + 2, m + 1, r);
        if (tree[2 * v + 1] > x) {
            return hib(2 * v + 1, l, m, x);
        } else {
            return hib(2 * v + 2, m + 1, r, x);
        }
    }
  }
};

LazySeg<ll, MX> p_seg, norm_seg; 

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);    
    int n, q; cin >> n >> q;
    vector<ll> p(n);
    vector<ll> norm(n);
    FOR(i, n) {
        cin >> p[i];
        norm[i] = p[i];
    }
    sort(p.begin(), p.end());
    sort(norm.begin(), norm.end());
    FORD(i, n) p[i] += (n - i);
    FOR(i, n) {
        p_seg.update(0, 0, n - 1, i, i, p[i]);
        norm_seg.update(0, 0, n - 1, i, i, norm[i]);
    }
    int gud = 0;
    auto lowb = [&] (ll v) {
        return norm_seg.lowb(0, 0, n - 1, v);
    };
    auto upb = [&] (ll v) {
        return norm_seg.hib(0, 0, n - 1, v);
    };
    FORD(i, n) {
        ll rem = (i == n - 1 ? -1 : p_seg.query(0, 0, n - 1, i + 1, n - 1));
        int pre = lowb(rem - n);
        if (pre == 1e9) pre = n;
        pre--;
        gud = max(gud, pre + 1);
    }
    FOR(t, q) {
        char qt; cin >> qt;
        if (qt == 'B') {
            ll x, y; cin >> x >> y;
            int ind = lowb(x);
            norm_seg.update(0, 0, n - 1, ind, n - 1, y);
            p_seg.update(0, 0, n - 1, ind, n - 1, y);
            ll rem = p_seg.query(0, 0, n - 1, ind, n - 1);
            int pre = lowb(rem - n);
            if (pre == 1e9) pre = n;
            pre--;
            gud = max(gud, pre + 1);
        } else if (qt == 'K') {
            ll x, y; cin >> x >> y;
            int ind = upb(x);
            if (ind == 1e9) ind = n;
            ind--;
            norm_seg.update(0, 0, n - 1, 0, ind, -y);
            p_seg.update(0, 0, n - 1, 0, ind, -y);
            ll rem = p_seg.query(0, 0, n - 1, ind + 1, n - 1);
            int pre = lowb(rem - n);
            if (pre == 1e9) pre = n;
            pre--;
            gud = max(gud, pre + 1);
        } else {
            cout << n - gud << '\n';
        }
    }
}
