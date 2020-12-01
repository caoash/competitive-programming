/*
 * Same as USACO Jan springboards.
 */

#include <bits/stdc++.h> 
using namespace std;
 
using ll = long long;
 
using vi = vector<int>;
using vl = vector<ll>;
#define pb push_back
#define rsz resize
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
 
using pi = pair<int,int>;
#define f first
#define s second
#define mp make_pair
 
const int MX = 200005;
const int MOD = (int) (1e9 + 7);
const ll INF = (ll) 1e18;

unordered_map<int, int> cx, cy;
map<pi, pi> st;
map<pi, pi> dp;
 
template<int SZ> struct Seg {
    pi tree[4*SZ];
 
    pi merge(pi a, pi b){
        if (a.f > b.f) return a;
        else if (b.f > a.f) return b;
        else {
            int ad = a.s + b.s;
            if (ad > 30013) ad -= 30013;
            return mp(a.f, ad);
        }
    }
    
    void update(int v, int l, int r, int i, pi x) {
        if (i > r || i < l) {
            return;
        } else if (l == r) {
            tree[v] = merge(tree[v], x);
            return;
        } else {
            int m = (l + r) / 2;
            update(2 * v + 1, l, m, i, x);
            update(2 * v + 2, m + 1, r, i, x);
            tree[v] = merge(tree[2 * v + 1], tree[2 * v + 2]);
        }
    }
 
    pi query(int v, int l, int r, int ql, int qr, int db) {
        if (l > qr || r < ql) {
            return mp(-1, -1);
        } else if (l >= ql && r <= qr) {
            return tree[v];
        } else {
            int m = (l + r) / 2;
            pi a = query(2 * v + 1, l, m, ql, qr, db);
            pi b = query(2 * v + 2, m + 1, r, ql, qr, db);
            return merge(a, b);
        }
    }
};
 
Seg<MX> orz;
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    vi xs, ys;
    vector<pair<pi, int>> evts;
    for (int i = 0; i < n; i++) {
        int x1, x2, y1, y2;
        cin >> x1 >> x2 >> y1 >> y2;
        pi lf = mp(x1, y1);
        pi sf = mp(x2, y2);
        st[sf] = lf;
        xs.pb(x1), ys.pb(y1);
        xs.pb(x2), ys.pb(y2);
        evts.pb(mp(lf, 0));
        evts.pb(mp(sf, 1));
    }
 
    sort(all(xs));
    sort(all(ys));
 
    int pt = 0;
    for (auto v : xs) cx[v] = pt++;
    pt = 0;
    for (auto v : ys) cy[v] = pt++;
    
    sort(all(evts));
 
    for (auto curr : evts) {
        pi rd = mp(cx[curr.f.f], cy[curr.f.s]);
        if (curr.s) {
            pi prev = st[curr.f];
            dp[rd] = dp[mp(cx[prev.f], cy[prev.s])];
            orz.update(0, 0, 2 * n, rd.s, dp[rd]);
        } else {
            pi gans = orz.query(0, 0, 2 * n, 0, rd.s, 0);
            dp[rd].f = gans.f + 1;
            dp[rd].s = max(1, gans.s);
        }
    }
 
    pi ans = orz.query(0, 0, 2 * n, 0, 2 * n, 1);
    cout << ans.f << " " << ans.s << '\n'; 
} 
