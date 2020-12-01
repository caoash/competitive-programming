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

const int MX = 100000;
const int MOD = (int) (1e9 + 7);
const int INF = 0x3f3f3f;

int n, k;
int dat[MX];

struct Node {
    int ans, cl, cr;
    vector<pi> l, r;
    Node() {
        ans = INF;
    }
};

struct Seg {
    Node tree[262144];

    void merge(Node &ret, Node &a, Node &b){
        ret.l.clear();
        ret.r.clear();
        ret.ans = min(a.ans, b.ans);
        bool done[k];
        memset(done, false, sizeof(done));
        for (auto x : b.r) {
            if (!done[x.s]) ret.r.pb(x), done[x.s] = true;
        }
        for (auto x : a.r) {
            if (!done[x.s]) ret.r.pb(x), done[x.s] = true;
        }
        memset(done, false, sizeof(done));
        for (auto x : a.l) {
            if (!done[x.s]) ret.l.pb(x), done[x.s] = true;
        }
        for (auto x : b.l) {
            if (!done[x.s]) ret.l.pb(x), done[x.s] = true;
        }
        bool used[k];
        memset(used, false, sizeof(used));
        int rhs = 0;
        int added[k];
        memset(added, 0, sizeof(added));
        int num = 0;
        auto ad = [&] (int v, int x) {
            if (added[v] == 0) ++num;
            if (x) ++added[v];
            else --added[v];
            if (added[v] == 0) --num;
        };
        int p = sz(b.l) - 1;
        for (auto x : b.l) ad(x.s, 1);
        for (int i = 0; i < sz(a.r); i++) {
            auto x = a.r[i];
            used[x.s] = true;
            ad(x.s, 1);
            while (p >= 0 && used[b.l[p].s]) {
                ad(b.l[p].s, -1);
                --p;
            }
            if (p < 0) break;
            if (num < k) continue;
            int best = b.l[p].f - b.cl + 1;
            rhs = a.cr - x.f + 1;
            ret.ans = min(ret.ans, best + rhs);
        }
        ret.cl = a.cl;
        ret.cr = b.cr;
    }

    void build(int v, int ql, int qr) {
        if (ql == qr) {
            Node init;
            {
                int x = dat[ql];
                if (k == 1) init.ans = 1;
                init.l.pb(mp(ql, x));
                init.r.pb(mp(qr, x));
                init.cl = ql;
                init.cr = qr;
            }
            tree[v] = init;
        } else {
            int m = (ql + qr) / 2;
            build(2 * v + 1, ql, m);
            build(2 * v + 2, m + 1, qr);
            merge(tree[v], tree[(v << 1) + 1], tree[(v << 1) + 2]);
        }
    }
    
    void update(int v, int ql, int qr, int i, int x) {
        if (i > qr || i < ql) {
            return;
        } else if (ql == qr) {
            Node init;
            {
                init.ans = (k == 1 ? 1 : INF);
                init.l.pb(mp(ql, x));
                init.r.pb(mp(qr, x));
                init.cl = ql;
                init.cr = qr;
            }
            tree[v] = init;
        } else {
            int m = (ql + qr) / 2;
            update(2 * v + 1, ql, m, i, x);
            update(2 * v + 2, m + 1, qr, i, x);
            merge(tree[v], tree[(v << 1) + 1], tree[(v << 1) + 2]);
        }
    }

    int query() {
        return tree[0].ans;
    }
};

Seg orz;

int main(){
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int m;
    cin >> n >> k >> m;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        x--;
        dat[i] = x;
    }
    orz.build(0, 0, n - 1);
    for (int i = 0; i < m; i++) {
        int qt; 
        cin >> qt;
        if (qt == 1) {
            int p, v; 
            cin >> p >> v;
            p--, v--;
            // dbg("UPD", p, v);
            orz.update(0, 0, n - 1, p, v);
        } else {
            int ans = orz.query();
            if (ans == INF) ans = -1;
            cout << ans << '\n';
        }
    }
}
