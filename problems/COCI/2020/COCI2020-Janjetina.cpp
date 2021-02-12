#include <bits/stdc++.h> 
using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)

#define F first
#define S second

const int MX = 100005;

template<class T, int SZ> struct BIT {
    T bit[SZ + 1];
    void upd(int p, int x) {
        for (; p <= SZ; p += (p & -p)) bit[p] += x;
    }
    T sum(int r) {
        T res = 0;
        for (; r; r -= (r & -r)) res += bit[r];
        return res;
    }
    T query(int l, int r) {
        return sum(r) - sum(l - 1); 
    }
};

BIT<int, MX> orz;
int larg[MX], dep[MX], sub[MX];
vector<pi> small;
bool blocked[MX];
int n, k;
ll ans = 0;
vector<pi> adj[MX];

int find(int v, int p, int root) {
    for (auto to : adj[v]) {
        if (to.F != p && !blocked[to.F]) {
            if (sub[to.F] > sub[root] / 2) {
                return find(to.F, v, root);
            }
        }
    }
    return v;
}

void dfs_pre(int v, int p) {
    sub[v] = 1;
    for (auto to : adj[v]) {
        if (to.F != p && !blocked[to.F]) {
            dep[to.F] = dep[v] + 1;
            larg[to.F] = max(larg[v], to.S);
            dfs_pre(to.F, v);
            sub[v] += sub[to.F]; 
        }
    }
}

void dfs_ord(int v, int p) {
    for (auto to : adj[v]) {
        if (to.F != p && !blocked[to.F]) {
            dfs_ord(to.F, v);
        }
    }
    small.push_back({larg[v], dep[v]});
}

ll comp(vector<pi> &ord) {
    ll res = 0;
    for (auto x : ord) {
        if (x.F - x.S - k >= 0) res += orz.query(1, x.F - x.S - k + 1);
        orz.upd(x.S + 1, 1);
    }
    for (auto x : ord) {
        orz.upd(x.S + 1, -1);
    }
    return res;
}

void merg(vector<pi> &a, vector<pi> &b) {
    vector<pi> c(a.size() + b.size());
    int p1 = 0, p2 = 0;
    while (p1 < a.size() || p2 < b.size()) {
        if (p1 >= a.size()) c[p1 + p2] = b[p2], p2++;
        else if (p2 >= b.size()) c[p1 + p2] = a[p1], p1++;
        else {
            if (a[p1].F < b[p2].F) {
                c[p1 + p2] = a[p1], p1++;
            } else {
                c[p1 + p2] = b[p2], p2++;
            }
        }
    }
    swap(c, a);
}

void go(int root) {
    dfs_pre(root, -1);
    int cent = find(root, -1, root);
    dep[cent] = 0, larg[cent] = 0;
    dfs_pre(cent, -1);
    vector<pi> big;
    big.push_back({larg[cent], dep[cent]});
    for (auto to : adj[cent]) {
        if (!blocked[to.F]) {
            small.clear();
            dfs_ord(to.F, cent);
            sort(small.begin(), small.end());
            ans -= comp(small);
            merg(big, small);
        }
    }
    ans += comp(big);
    blocked[cent] = true;
    for (pi to : adj[cent]) {
        if (!blocked[to.F]) {
            go(to.F);
        }
    }
}


int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> k;
    FOR(i, n - 1) {
        int u, v, w; cin >> u >> v >> w;
        u--, v--;
        adj[u].push_back({v, w}), adj[v].push_back({u, w});
    }
    go(0);
    cout << 2 * ans << '\n';
}

