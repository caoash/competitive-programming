#include <bits/stdc++.h> 
using namespace std;

typedef long long ll;

#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)

#define F first
#define S second

const ll MX = (1LL << 30);

int cnt = 1;

struct Node {
    ll sum;
    int l, r;     
    Node() {
        l = -1, r = -1;
        sum = 0;
    }
};

struct RageTree{
    vector<Node> tree;

    void ins(int v, int l, int r, int x) {
        if (x > r || x < l) return; 
        if (v >= tree.size()) tree.resize(v + 1);
        if (l != r) {
            // cout << "AT: " << v << " " << l << " " << r << '\n';
            int mid = (l + r) / 2;
            if (x <= mid) {
                int go = tree[v].l;
                if (go == -1) {
                    go = ++cnt;
                    tree[v].l = go;
                }
                ins(go, l, mid, x);
            } else {
                int go = tree[v].r;
                if (go == -1) {
                    go = ++cnt;
                    tree[v].r = go;
                }
                ins(go, mid + 1, r, x);
            }
        }
    }

    void upd(int v, int l, int r, int i, int x) {
        if (i > r || i < l) return;
        if (v >= tree.size()) tree.resize(v + 1);
        if (l == r) {
            tree[v].sum += x;
        } else {
            ll res = 0;
            int mid = (l + r) / 2;
            if (tree[v].l != -1) {
                upd(tree[v].l, l, mid, i, x);
                res += tree[tree[v].l].sum;
            }
            if (tree[v].r != -1) {
                upd(tree[v].r, mid + 1, r, i, x);
                res += tree[tree[v].r].sum;
            }
            tree[v].sum = res;
            // dbg(v, tree[v].sum);
        }
    }

    int query(int v, int l, int r, int ql, int qr) {
        if (l > qr || r < ql) return 0;
        if (v >= tree.size()) tree.resize(v + 1);
        if (l >= ql && r <= qr) {
            // dbg(v, l, r, ql, qr, tree[v].sum);
            return tree[v].sum;
        }
        else {
            // cout << v << " " << tree[v].l << " " << tree[v].r << '\n';
            // dbg(v, l, r, tree[v].sum);
            int mid = (l + r) / 2;
            ll res = 0;
            if (tree[v].l != -1) {
                res += query(tree[v].l, l, mid, ql, qr);
            }
            if (tree[v].r != -1) {
                res += query(tree[v].r, mid + 1, r, ql, qr);
            }
            return res;
        }
    }
};

RageTree bef, aft;

int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; ll k;
    cin >> n >> k;
    vector<ll> events;
    FOR(i, n) {
        ll l, r; cin >> l >> r;
        events.push_back(l);
        events.push_back(r);
        bef.ins(1, 1, MX, l);
        bef.ins(1, 1, MX, r);
        aft.ins(1, 1, MX, l);
        aft.ins(1, 1, MX, r);
        bef.upd(1, 1, MX, r, 1);
        aft.upd(1, 1, MX, l, 1);
    }
    sort(events.begin(), events.end());
    int ans = 0;
    for (auto x : events) {
        ll lb = x, rb = x + k;
        if (rb >= lb) {
            ans = max(ans, n - bef.query(1, 1, MX, 1, lb - 1) - aft.query(1, 1, MX, rb + 1, MX));
        }
    }
    cout << ans << '\n';
}

