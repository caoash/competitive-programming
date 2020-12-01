/*
Notice that you win of the set of elements for some prefix is the same in all 3 arrays. You rewrite this condition as the
maximum occurance of some number is <= K for all numbers. Then, we can set it to K - cnt(x) which lets you find the first 0
by doing segtree walk and update with lazy prop.
*/

#include <bits/stdc++.h> 
using namespace std;

using ll = long long;

using vi = vector<int>;
#define pb push_back
#define rsz resize
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using pi = pair<int,int>;
#define f first
#define s second
#define mp make_pair

const int MX = 100005;

#include <bits/stdc++.h> 
using namespace std;

using ll = long long;

using vi = vector<int>;
#define pb push_back
#define rsz resize
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using pi = pair<int,int>;
#define f first
#define s second
#define mp make_pair

int n; int a[3][MX];

template<class T, int SZ> struct LazySeg{
  T tree[4 * SZ], lazy[4 * SZ];

  T merge(T a, T b){
    return min(a, b);
  }

  void build(int v, int l, int r) {
    if (l == r) {
        tree[v] = (l + 1);
        return;
    }
    else {
        int m = (l + r) / 2;
        build(2 * v + 1, l, m);
        build(2 * v + 2, m + 1, r);
        tree[v] = merge(tree[2 * v + 1], tree[2 * v + 2]);
        return;
    }
  } 

  void prop(int v, int l, int r){
    if (lazy[v] != 0) {
      tree[v] += lazy[v];
      if (l != r) {
        lazy[2 * v + 1] += lazy[v];
        lazy[2 * v + 2] += lazy[v];
      }
      lazy[v] = 0;
    }
    return;
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
    tree[v] = merge(tree[2 * v + 1], tree[2 * v +2]);
    return;
  }

  void query(int v, int l, int r, int &best) {
    prop(v, l, r); 
    if (tree[v] != 0) {
        best = min(best, n);
        return;
    }
    if (l == r) {
        best = min(best, l);
        return;
    } else {
      int m = (l + r) / 2;
      prop(2 * v + 1, l, m);
      prop(2 * v + 2, m + 1, r);
      tree[v] = merge(tree[2 * v + 1], tree[2 * v + 2]);
      if (tree[2 * v + 1] == 0) {
        query(2 * v + 1, l, m, best);
      }
      else {
        query(2 * v + 2, m + 1, r, best);
      }
      return;
    }
  }
};

LazySeg<int, MX> orz; int mi[MX]; int pos[3][MX];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int q; cin >> n >> q;
    for (int i = 0; i < 3; i++) for (int j = 0; j < n; j++) {
        cin >> a[i][j];
        mi[a[i][j]] = max(mi[a[i][j]], j);
        pos[i][a[i][j]] = j;
    }
    orz.build(0, 0, n - 1);
    for (int i = 1; i <= n; i++) {
        orz.update(0, 0, n - 1, mi[i], n - 1, -1);
    }
    int cbest = n;
    auto relax = [&] () {
        cbest = n;
        orz.query(0, 0, n - 1, cbest);
    };
    relax();
    auto swp = [&] (int p, int i, int j) {
        swap(pos[p][i], pos[p][j]);
        mi[i] = max({pos[0][i], pos[1][i], pos[2][i]});
        mi[j] = max({pos[0][j], pos[1][j], pos[2][j]});
    };
    for (int i = 0; i < q; i++) {
        int qt; cin >> qt;
        if (qt == 1) {
            int x; cin >> x;
            if (mi[x] <= cbest) {
                cout << "DA" << '\n';
            }
            else {
                cout << "NE" << '\n';
            }
        }
        else {
            int p, x, y; cin >> p >> x >> y;
            p--;
            orz.update(0, 0, n - 1, mi[x], n - 1, 1);
            orz.update(0, 0, n - 1, mi[y], n - 1, 1);
            swp(p, x, y);
            orz.update(0, 0, n - 1, mi[x], n - 1, -1);
            orz.update(0, 0, n - 1, mi[y], n - 1, -1);
            relax();
        }
    }
}