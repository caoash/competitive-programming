/*
 * Observe that the bottleneck of some operation to x is the max between a and x, and it's "blocked" by the closest element on the other side that's larger.
 *
 * So you just need to implement the updates and a max segtree, while doing segtree walk to help support queries fast enough. To deal with updates, there's a lot of ways to 
 * do it. Personally, I did it like this:
 *
 * If the original array is 1 2 3 4 5, and you update 1 to be 4 (second largest), then you actually update it to be 5 and increase anything greater. 
 *
 * So, 1 2 3 4 5 => 5 2 3 4 6 since the relative order is still ok then the max queries are fine too. There's a lot of small details to figure out, though.
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

template<class T, int SZ> struct Seg{
    T tree[4*SZ];
    T merge(T a, T b){
        return max(a, b);
    }
    
    void update(int v, int l, int r, int i, T x) {
        if (i > r || i < l) {
            return;
        } else if (l == r) {
            tree[v] = x;
        } else {
            int m = (l + r) / 2;
            update(2 * v + 1, l, m, i, x);
            update(2 * v + 2, m + 1, r, i, x);
            tree[v] = merge(tree[2 * v + 1], tree[2 * v + 2]);
        }
    }

    T query2(int v, int l, int r, int ql, int qr) {
        if (ql > r || qr < l) {
            return 0;
        }
        if (l >= ql && r <= qr) {
            return tree[v];
        }
        else {
            int m = (l + r) / 2;
            T a = query2(2 * v + 1, l, m, ql, qr);
            T b = query2(2 * v + 2, m + 1, r, ql, qr);
            return merge(a, b);
        }
    }

    T query(int v, int l, int r, int val, int dir) {
        if (r < l || tree[v] <= val) {
            return -1;
        }
        else if(l == r) {
            return l;
        }
        else {
            int m = (l + r) / 2;
            if (dir) {
                if (tree[2 * v + 2] > val) { 
                    return query(2 * v + 2, m + 1, r, val, dir);
                }
                else {
                    return query(2 * v + 1, l, m, val, dir);
                }
            }
            else {
                if (tree[2 * v + 1] > val) {
                    return query(2 * v + 1, l, m, val, dir); 
                }
                else {
                    return query(2 * v + 2, m + 1, r, val, dir);
                }
            }
        }
    }
};

const int MX = 250005;

int pos[MX];

Seg<int, MX> lft, rgt; 

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, a; cin >> n >> a;
    a--;
    vi d(n);
    for (int i = 0; i < n; i++) {
        cin >> d[i]; 
        pos[d[i]] = i;
        if(i < a) lft.update(0, 0, n - 1, i, d[i]);
        else if (i > a) rgt.update(0, 0, n - 1, i, d[i]);
    }
    int q; cin >> q;
    vector<pi> top;
    for (int i = max(1, n - 9); i <= n; i++) {
        top.pb(mp(i, pos[i]));
    }
    vector<pi> order;
    while(q--) {
        char qt; cin >> qt; 
        if (qt == 'E') {
            int i, e; cin >> i >> e;
            i--;
            for (int j = 0; j < e - 1; j++) {
                if (top.back().s != i) {
                    int v = top.back().f; int p = top.back().s;
                    order.pb(mp(v + 1, p));
                    if(p < a) lft.update(0, 0, n - 1, p, v + 1);
                    else if(p > a) rgt.update(0, 0, n - 1, p, v + 1);
                    d[p] = v + 1;
                }
                else {
                    j--;
                }
                top.pop_back();
            }
            int prev = d[i];
            d[i] = top.back().f + 1;
            if(i < a) lft.update(0, 0, n - 1, i, top.back().f + 1);
            else if(i > a) rgt.update(0, 0, n - 1, i, top.back().f + 1);
            order.pb(mp(top.back().f + 1, i));
            bool found = false;
            while (!top.empty()) {
                if(top.back().f != prev) {
                     order.pb(mp(top.back().f, top.back().s));
                }
                else {
                     found = true;
                }
                top.pop_back(); 
            }
            if (!found) order.pop_back();
            reverse(all(order));
            for (pi x : order) {
                top.pb(x);
            }
            order.clear();
        }
        else {
            int x; cin >> x;
            x--;
            if (x == a) { 
                cout << 0 << '\n';
                continue;
            }
            int best = 0;
            if (x < a) best = lft.query2(0, 0, n - 1, x, a - 1);
            else if (x > a) best = rgt.query2(0, 0, n - 1, a + 1, x);
            if (x < a) {
                int ans = rgt.query(0, 0, n - 1, best, 0);
                if (rgt.query2(0, 0, n - 1, a + 1, n - 1) <= best) {
                    ans = n;
                }
                cout << (ans - x - 1) << '\n';
            }
            else if(x > a) {
                int ans = lft.query(0, 0, n - 1, best, 1);
                if (lft.query2(0, 0, n - 1, 0, a - 1) <= best) {
                    ans = -1;
                }
                cout << (x - ans - 1) << '\n';
            }
        }
    }
}

