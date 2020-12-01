/*
 * First the second subtask gives way to some idea about iterating over rows.
 *
 * Then realize that you just need to store segments that are visitable from the previous row.
 *
 * Finally notice a lot of rows are repeated, so do some math to figure them out.
 */

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

vector<pi> pts;
int main(){
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; ll m; cin >> m >> n;
    for (int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        pts.pb(mp(x, y));
    }
    sort(all(pts));
    set<pi> bad;
    pi prev = mp(0, 0);
    ll ans = 0;
    vector<pi> add;
    auto solve = [&] (int l, int r) {
        if (r < l) return;
        pi curr = mp(l, r);
        auto it = bad.lb(mp(curr.f, INT_MIN));
        if (it != bad.end()) {
            if ((it -> s) <= curr.s) {
                int fst = max(curr.f, (it -> s));
                ans += (curr.s - fst + 1);
                add.pb(mp(curr.s, fst));
            }
        }
        return;
    };
    auto relax = [&] () {
        bad.clear();
        for (auto x : add) bad.insert(x);
        add.clear();
        return;
    };
    add.pb(mp(1, 1));
    for (int i = 0; i < sz(pts); i++) {
        auto x = pts[i];
        if (x.f == prev.f) {
            solve(prev.s + 1, x.s - 1);
            if (i == sz(pts) - 1 || pts[i + 1].f != x.f) {
                solve(x.s + 1, m);
            }
        } else {
            relax();
            if (x.f != prev.f + 1 && !bad.empty()) {
                int lft = m;
                for (auto y : bad) lft = min(lft, y.s);
                solve(lft, m);
                ans += (m - lft + 1) * (x.f - prev.f - 2);
                relax();
            } 
            solve(1, x.s - 1);
            if (i == sz(pts) - 1 || pts[i + 1].f != x.f) {
                solve(x.s + 1, m);
            }
        }
        prev = x;
    }
    relax();
    if (prev.f != m && !bad.empty()) {
        int lft = m;
        for (auto y : bad) lft = min(lft, y.s);
        solve(lft, m);
        if (m - prev.f > 1) ans += (m - lft + 1) * (m - prev.f - 1);
    }
    cout << ans << '\n';
}

