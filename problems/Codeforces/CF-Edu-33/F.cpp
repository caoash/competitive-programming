#include <bits/stdc++.h> 
using namespace std;

using ll = long long;

using vi = vector<int>;
using vl = vector<ll>;
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define lb lower_bound
#define ub upper_bound

using pi = pair<int,int>;
#define f first
#define s second
#define mp make_pair

const int MX = 200005;
const int MOD = (int) (1e9 + 7);
const ll INF = (ll) 1e18;

pi init[MX]; //depth, a[i] 

struct Node {
    vector<pi> vals;
    void relax() {
        for (int i = 1; i < sz(vals); i++) {
            vals[i].s = min(vals[i].s, vals[i - 1].s);
        }
    }
};

template<int SZ> struct Seg {
    Node tree[4*SZ];

    Node merge(Node &a, Node &b){
        Node ret;
        int p1 = 0, p2 = 0;
        while (p1 < sz(a.vals) || p2 < sz(b.vals)) {
            if (p1 < sz(a.vals) && p2 < sz(b.vals)) {
                if (a.vals[p1] < b.vals[p2]) {
                    ret.vals.pb(a.vals[p1++]);
                } else {
                    ret.vals.pb(b.vals[p2++]);
                }
            } else if (p1 < sz(a.vals)) {
                ret.vals.pb(a.vals[p1++]);
            } else {
                ret.vals.pb(b.vals[p2++]);
            }
        }
        ret.relax();
        return ret;
    }

    void build(int v, int l, int r) {
        if (l == r) {
            tree[v].vals.pb(init[l]); 
        } else {
            int m = (l + r) / 2;
            build(2 * v + 1, l, m);
            build(2 * v + 2, m + 1, r);
            tree[v] = merge(tree[2 * v + 1], tree[2 * v + 2]);
        }
    }
    
    int query(int v, int l, int r, int ql, int qr, int x) {
        if (l > qr || r < ql) {
            return INT_MAX;
        } else if (l >= ql && r <= qr) {
            auto &cur = tree[v].vals;
            int lo = 0; int hi = sz(cur) - 1;
            int ret = -1;
            while (lo <= hi) {
                int mid = (lo + hi) / 2;
                if (cur[mid].f <= x) {
                    ret = mid;
                    lo = mid + 1;
                } else {
                    hi = mid - 1;
                }
            }
            if (ret == -1) return INT_MAX;
            return cur[ret].s;
        } else {
            int m = (l + r) / 2;
            int a = query(2 * v + 1, l, m, ql, qr, x);
            int b = query(2 * v + 2, m + 1, r, ql, qr, x);
            return min(a, b);
        }
    }
};

int dep[MX], a[MX], sub[MX], pos[MX];
vi adj[MX];
vi ord;

void dfs(int v, int p) {
    sub[v] = 1;
    ord.pb(v);
    for (int to : adj[v]) {
        if (to != p) {
            dep[to] = dep[v] + 1;
            dfs(to, v);
            sub[v] += sub[to];
        }
    }
}

Seg<MX> orz;

int main(){
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, r; cin >> n >> r;
    r--;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        u--, v--;
        adj[u].pb(v), adj[v].pb(u);
    }
    dfs(r, -1);
    for (int i = 0; i < n; i++) {
        init[i] = mp(dep[ord[i]], a[ord[i]]);
        pos[ord[i]] = i;
    }
    orz.build(0, 0, n - 1);
    int m; cin >> m;
    int prev = 0;
    for (int i = 0; i < m; i++) {
        int p, q; cin >> p >> q;
        p = ((p + prev) % n) + 1;
        q = ((q + prev) % n);
        p--;
        prev = orz.query(0, 0, n - 1, pos[p], pos[p] + sub[p] - 1, dep[p] + q);
        cout << prev << '\n';
    }
}

