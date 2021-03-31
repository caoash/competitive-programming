#include <bits/stdc++.h> 
using namespace std;
 
typedef long long ll;
 
#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)
 
#define F first
#define S second

const int MX = 65537;

int tree[4 * MX];

int qry(int v, int l, int r, int ql, int qr) {
    if (l > qr || r < ql) return 0;
    if (l >= ql && r <= qr) {
        return tree[v];
    } else {
        int m = (l + r) / 2;
        return qry(2 * v + 1, l, m, ql, qr) + qry(2 * v + 2, m + 1, r, ql, qr);
    }
}

void upd(int v, int l, int r, int i, int x) {
    if (l > i || r < i) return;
    if (l == r) {
        tree[v] += x;
    } else {
        int m = (l + r) / 2;
        upd(2 * v + 1, l, m, i, x);
        upd(2 * v + 2, m + 1, r, i, x);
        tree[v] = tree[2 * v + 1] + tree[2 * v + 2];
    }
}

map<int, int> cc;
 
int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);    
    int n; cin >> n;
    vector<int> a(n), b(n);
    FOR(i, n) cin >> a[i], b[i] = a[i];
    sort(a.begin(), a.end());
    int c = 0;
    FOR(i, n) {
        if (!cc.count(a[i])) {
            cc[a[i]] = c++;
        }
    }
    ll ans = 0;
    FOR(i, n) {
        ans += qry(0, 0, n - 1, cc[b[i]] + 1, n - 1);
        upd(0, 0, n - 1, cc[b[i]], 1);
    }
    cout << ans << '\n';
}

