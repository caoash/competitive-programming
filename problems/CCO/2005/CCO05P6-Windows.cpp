#include <bits/stdc++.h> 
using namespace std;

typedef long long ll;

#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)

#define F first
#define S second

const int mxN = 10005;

struct Node_x {
    int l, r;
    pair<int, int> upd_v;

    Node_x() {
        l = -1, r = -1;
    }
};

Node_x tree_x[1000005];
int cnt_x = 0;

struct segtree_x {
    void ins(int v, int l, int r, int x) {
        // // dbg(v, cnt_x);
        if (x > r || x < l) {
            return;
        } else {
            if (l != r) {
                // dbg(v, l, r, x, cnt_x, tree_x[v].l, tree_x[v].r);
                int mid = (l + r) / 2; 
                if (x <= mid) {
                    int nxt = tree_x[v].l; 
                    if (nxt == -1) {
                        tree_x[v].l = ++cnt_x;
                        nxt = cnt_x;
                    }
                    ins(nxt, l, mid, x);
                } else {
                    int nxt = tree_x[v].r;
                    if (nxt == -1) {
                        tree_x[v].r = ++cnt_x;
                        nxt = cnt_x;
                    }
                    ins(nxt, mid + 1, r, x);
                }
            }
        }
    }

    void upd(int v, int l, int r, int ul, int ur, int x, int time) {
        if (l >= ul && r <= ur) {
            // assert(upd_v.size() > v);
            // // dbg("SET", v, l, r, ul, ur, x, time);
            tree_x[v].upd_v = {x, time};
            return;
        } else {
            int mid = (l + r) / 2; 
            if (tree_x[v].l != -1) upd(tree_x[v].l, l, mid, ul, ur, x, time);
            if (tree_x[v].r != -1) upd(tree_x[v].r, mid + 1, r, ul, ur, x, time);
        }
    }

    void query(int v, int l, int r, int qx, pair<int, int> &best) {
        if (qx > r || qx < l) return;
        // assert(upd_v.size() > v);
        // // dbg(v, l, r, qx, best);
        // // dbg(v, tree_x[v].upd_v);
        if (tree_x[v].upd_v.S > best.S) best = tree_x[v].upd_v;     
        // // dbg(v, l, r, qx, best);
        if (l != r) {
            int mid = (l + r) / 2;
            if (tree_x[v].l != -1) query(tree_x[v].l, l, mid, qx, best);
            if (tree_x[v].r != -1) query(tree_x[v].r, mid + 1, r, qx, best);
        }
    }
};

struct Node_y {
    int l, r;
    segtree_x upd_v;
    int ctr;
    Node_y() {
        l = -1, r = -1, ctr = -1;
    }
};

Node_y tree_y[10005];
int cnt_y = 0;

struct segtree_y {
    void ins(int v, int l, int r, int x, int y) {
        if (y > r || y < l) {
            return;
        } else {
            // dbg("INS", l, r, x);
            if (tree_y[v].ctr == -1) tree_y[v].ctr = ++cnt_x;
            tree_y[v].upd_v.ins(tree_y[v].ctr, 0, mxN - 1, x);
            if (l != r) {
                int mid = (l + r) / 2; 
                if (y <= mid) {
                    int nxt = tree_y[v].l;
                    if (nxt == -1) {
                        tree_y[v].l = ++cnt_y;
                        // // dbg(v, tree_y[v].l);
                        nxt = cnt_y;
                    }
                    ins(nxt, l, mid, x, y);
                } else {
                    int nxt = tree_y[v].r;
                    if (nxt == -1) {
                        tree_y[v].r = ++cnt_y;
                        // dbg(v, tree_y[v].r);
                        nxt = cnt_y;
                    }
                    ins(nxt, mid + 1, r, x, y);
                }
            }
        }
    }

    void upd(int v, int l, int r, int x1, int x2, int y1, int y2, int x, int time) {
        if (l >= y1 && r <= y2) {
            tree_y[v].upd_v.upd(tree_y[v].ctr, 0, mxN - 1, x1, x2, x, time);
            // // dbg("SET", v, l, r, y1, y2, time);
            return;
        } else {
            int mid = (l + r) / 2; 
            if (tree_y[v].l != -1) upd(tree_y[v].l, l, mid, x1, x2, y1, y2, x, time);
            if (tree_y[v].r != -1) upd(tree_y[v].r, mid + 1, r, x1, x2, y1, y2, x, time);
        }
    }

    void query(int v, int l, int r, int qx, int qy, pair<int, int> &best) {
        if (qy > r || qy < l) return;
        // // dbg(v, l, r, "QUERY", qx, best);
        tree_y[v].upd_v.query(tree_y[v].ctr, 0, mxN - 1, qx, best);
        // // dbg(v, l, r, "QUERY", qx, best);
        if (l != r) {
            int mid = (l + r) / 2;
            if (tree_y[v].l != -1) query(tree_y[v].l, l, mid, qx, qy, best);
            if (tree_y[v].r != -1) query(tree_y[v].r, mid + 1, r, qx, qy, best);
        }
    }
} ans;

int query(int x, int y) {
    pair<int, int> res = {-1e9, -1e9};
    ans.query(0, 0, mxN - 1, x, y, res);
    return res.F;
}

void update(int x1, int x2, int y1, int y2, int x, int time) {
    ans.upd(0, 0, mxN - 1, x1, x2, y1, y2, x, time);
}

void ins(int x, int y) {
    ans.ins(0, 0, mxN - 1, x, y);
}

array<int, 4> windows[mxN];
pair<int, int> queries[mxN];

int ctr = 1;

segtree_x wtuoo;

int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int R, C; cin >> C >> R;
    int n; cin >> n;
    FOR(i, n) {
        int x1, y1, x2, y2; 
        cin >> x1 >> y2 >> x2 >> y1;
        x1--, y1--, x2--, y2--;
        windows[i] = {x1, x2, y1, y2};
    }
    int q; cin >> q;
    FOR(i, q) {
        int x, y; cin >> x >> y;
        x--, y--;
        ins(x, y);
        queries[i] = {x, y};
    }
    FOR(i, n) {
        auto v = windows[i];
        update(v[0], v[1], v[2], v[3], i + 1, ctr++);
    }
    FOR(i, q) {
        auto wtmoo = queries[i];
        int x = wtmoo.F, y = wtmoo.S;
        int val = query(x, y);
        cout << val << '\n';
        if (val > 0) {
            array<int, 4> &cur = windows[val - 1];
            update(cur[0], cur[1], cur[2], cur[3], val, ctr++);
        }
    }
}
