#include <bits/stdc++.h> 
#include <cassert>
using namespace std;
 
typedef long long ll;
 
#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)
 
#define F first
#define S second

const int MX = 300005;

int n;
ll tree[4 * MX];
pair<ll, ll> lazy[4 * MX];

void apply(int v, ll a, ll b) {
    lazy[v].F += a;
    lazy[v].S += b;
}

void prop(int v, int l, int r) {
    { // apply lazy[v]
        ll siz = (r - l + 1);
        ll sum = lazy[v].F * siz + lazy[v].S * (siz * (siz - 1) / 2);
        tree[v] += sum; 
    }
    if (l != r) {
        // merge lazy[v] with left and right
        int mid = (l + r) / 2;
        apply(2 * v + 1, lazy[v].F, lazy[v].S);
        apply(2 * v + 2, lazy[v].F + (lazy[v].S * (mid - l + 1)), lazy[v].S);
    }
    lazy[v].F = 0, lazy[v].S = 0;
}

void upd(int v, int l, int r, int ul, int ur, ll us, ll ua) {
    prop(v, l, r);
    if (l >= ul && r <= ur) {
        ll st = us + ua * (l - ul);
        apply(v, st, ua);
        prop(v, l, r);
    } else if (l > ur || r < ul) {
        return;
    } else {
        int mid = (l + r) / 2;
        upd(2 * v + 1, l, mid, ul, ur, us, ua);
        upd(2 * v + 2, mid + 1, r, ul, ur, us, ua);
        tree[v] = tree[2 * v + 1] + tree[2 * v + 2];
    }
}

ll query(int v, int l, int r, int ql, int qr) {
    prop(v, l, r);
    if (l >= ql && r <= qr) {
        return tree[v];  
    } else if (l > qr || r < ql) {
        return 0;
    } else {
        int mid = (l + r) / 2;
        ll a = query(2 * v + 1, l, mid, ql, qr);
        ll b = query(2 * v + 2, mid + 1, r, ql, qr);
        return a + b;
    }
}

void Upd(int ul, int ur, ll us, ll ua) {
    upd(0, 0, n - 1, ul, ur, us, ua);
}

ll Query(int ql, int qr) {
    return query(0, 0, n - 1, ql, qr);
}

pair<int, int> at[MX];
 
int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);    
    int q; cin >> n >> q;
    FOR(i, q) {
        char qt; cin >> qt;
        if (qt == 'P') {
            int x, s, a; cin >> x >> s >> a;
            x--;
            Upd(x, x, s, 0);
            int v = s / a;
            Upd(x - v, x - 1, s - v * a, a);
            Upd(x + 1, x + v, s - a, -a);
            at[x] = make_pair(s, a);
        } else if (qt == 'U') {
            int x; cin >> x;
            x--;
            pair<int, int> &cur = at[x];
            assert(cur.F != -1);
            int s = cur.F, a = cur.S;
            int v = s / a;
            Upd(x, x, -s, 0);
            Upd(x - v, x - 1, -s + v * a, -a);
            Upd(x + 1, x + v, -s + a, a);
            at[x] = make_pair(-1, -1);
        } else if (qt == 'Z') {
            int cl, cr; cin >> cl >> cr;
            cl--, cr--;
            ll res = Query(cl, cr);
            cout << res / (cr - cl + 1) << endl;
        }
    }
}

