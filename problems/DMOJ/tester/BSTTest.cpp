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

vector<Node> tree;

multiset<int> stuff;

void ins(int v, int l, int r, int x) {
    if (x > r || x < l) return; 
    if (v >= tree.size()) tree.resize(v + 1);
    if (l != r) {
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
    }
}

int query(int v, int l, int r, int ql, int qr) {
    if (l > qr || r < ql) return 0;
    if (v >= tree.size()) tree.resize(v + 1);
    if (l >= ql && r <= qr) {
        return tree[v].sum;
    }
    else {
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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, q; cin >> n >> q;
    set<int> alr;
    FOR(i, n) {
        int x; cin >> x;
        if (!alr.count(x)) {
            ins(1, 1, MX, x);
            alr.insert(x);
        }
        upd(1, 1, MX, x, 1);
        stuff.insert(x);
    }
    ll ans = 0;
    FOR(i, q) {
        char qt; cin >> qt;
        int v; cin >> v;
        v ^= ans;
        if (qt == 'S') {
            ll lo = 1, hi = MX;
            if (!alr.count(v)) {
                ins(1, 1, MX, v);
                alr.insert(v);
            } 
            while (lo <= hi) {
                int mid = (lo + hi) / 2;
                ll cur = query(1, 1, MX, 1, mid);
                // cout << "MID, CUR: " << mid << " " << cur << '\n';
                if (cur >= v) {
                    hi = mid - 1;
                    ans = mid;
                } else {
                    lo = mid + 1;
                }
            }
            cout << ans << '\n';
        } else if (qt == 'I') {
            if (!alr.count(v)) {
                ins(1, 1, MX, v);
                alr.insert(v);
            } 
            stuff.insert(v);
            upd(1, 1, MX, v, 1);
        } else if (qt == 'R') {
            int num = query(1, 1, MX, v, v);
            if (num > 0) upd(1, 1, MX, v, -1);
            if (stuff.count(v)) {
                stuff.erase(stuff.find(v));
            }
        } else if (qt == 'L') {
            if (!alr.count(v)) {
                ins(1, 1, MX, v);
                alr.insert(v);
            } 
            ll num = query(1, 1, MX, v, v);
            if (num == 0) {
                ans = -1;
                cout << -1 << '\n';
            } else {
                ans = query(1, 1, MX, 1, v - 1) + 1;
                cout << ans << '\n';
            }
        }
    }
    for (auto x : stuff) cout << x << " ";
    if (!stuff.empty()) cout << '\n';
}

