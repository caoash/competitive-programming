/*
 * Consider some path from u to v.
 *
 * Define the range of some guy u as [u, first before u that has edge cut].
 *
 * Define the range of v similarly.
 *
 * Then if there exists a bridge between [l1, r1] and [l2, r2], then u can reach v.
 *
 * Try to view it as points.
 * 
 * Problem reduces to: add a point, check if rectangle contains point.
 * Another constraint: points are always monotoncially increasing
 * - binary search for first point with x >= left edge of rect and y >= bottom edge of rect
 * - check if x <= right edge of rect and y <= top edge of rect
 *
 * You need to do something special if the queries are not two node on opposite sides.
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

#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <class T> using PeanutButter = tree<T, null_type, less<T>, 
    rb_tree_tag, tree_order_statistics_node_update>; 
#define ook order_of_key
#define fbo find_by_order

PeanutButter<pi> pts;
set<int> bad[2];
set<int> pre[2];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m; cin >> n >> m;
    bad[0].insert(n), bad[1].insert(n);
    pre[0].insert(1), pre[1].insert(1);
    auto has = [&] (pi xs, pi ys) {
        int ans = -1;
        int lo = 0, hi = sz(pts) - 1;
          ////dbg(pts);
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            pi cur = *pts.fbo(mid);
             //dbg(mid, cur);
            if (cur.f >= xs.f && cur.s >= ys.f) {
                hi = mid - 1;
                ans = mid;
            } else {
                lo = mid + 1;
            }
        }
        if (ans == -1) return false;
        else {
            pi cur = *pts.fbo(ans);
             //dbg(cur);
            if (cur.f <= xs.s && cur.s <= ys.s) {
                return true;
            } 
            return false;
        }
    };
    for (int i = 0; i < m; i++) {
        char qt; cin >> qt;
        if (qt == 'A') {
            int x, y; cin >> x >> y;
            if (x > y) swap(x, y);
            if (y > n) y -= n; 
            pts.insert(mp(x, y));
             //dbg("AD", x, y);
        } else if (qt == 'B') {
            int x, y; cin >> x >> y;
              ////dbg("REM", x, y);
            bool c = (x > n);
            x -= (n * c);
            y -= (n * c);
            bad[c].insert(min(x, y));
            pre[c].insert(max(x, y));
        } else {
            int x, y; cin >> x >> y;
            int c = (x > n), c2 = (y > n);
            x -= (n * c);
            y -= (n * c2);
            if (c == c2) {
                 //dbg("QUERY", x, y);
                if (!c) {
                    if (x < y) {
                        int go = *(bad[c].lb(x));
                        if (go >= y) cout << "DA\n";
                        else cout << "NE\n";
                    } else {
                        int lo = 0, hi = sz(pts) - 1;
                        int ans = -1;
                        while (lo <= hi) {
                            int mid = (lo + hi) / 2;
                            pi curr = *(pts.fbo(mid));
                            if (curr.f >= x) {
                                hi = mid - 1;
                                ans = mid;
                            } else {
                                lo = mid + 1;
                            }
                        }
                        if (ans == -1) cout << "NE\n";
                        else {
                            pi fir = *(pts.fbo(ans));
                            int fbad = *(bad[c].lb(x));
                            if (fir.f > fbad) {
                                cout << "NE\n";
                            } else {
                                lo = 0, hi = sz(pts) - 1;            
                                ans = -1;
                                while (lo <= hi) {
                                    int mid = (lo + hi) / 2;
                                    pi curr = *(pts.fbo(mid));
                                    if (curr.f <= y) {
                                        lo = mid + 1; 
                                        ans = mid;
                                    } else {
                                        hi = mid - 1;
                                    }
                                }
                                if (ans == -1) cout << "NE\n";
                                else {
                                    pi sec = *(pts.fbo(ans));
                                    int pbad = *(--pre[c].ub(y));
                                    if (sec.f < pbad) cout << "NE\n";
                                    else {
                                        int xsid = fir.s, ysid = sec.s;
                                        if (*(bad[c ^ 1].lb(ysid)) >= xsid) {
                                            cout << "DA\n";
                                        } else {
                                            cout << "NE\n";
                                        }
                                    }
                                }
                            }
                        }
                        // find first point f >= x
                        // find last point f <= y
                        // check if their endpoints are in same region
                    }
                } else {
                    if (y < x) {
                        int go = *(--pre[c].ub(x));
                         //// dbg(go, x, y);
                        if (go <= y) cout << "DA\n";
                        else cout << "NE\n";
                    } else {
                        // find first point f <= x
                        // find first point f >= y
                        int lo = 0, hi = sz(pts) - 1;
                        int ans = -1;
                        while (lo <= hi) {
                            int mid = (lo + hi) / 2;
                            pi curr = *(pts.fbo(mid));
                            if (curr.s <= x) {
                                lo = mid + 1;
                                ans = mid;
                            } else {
                                hi = mid - 1;
                            }
                        }
                        if (ans == -1) cout << "NE\n";
                        else {
                            pi fir = *(pts.fbo(ans));
                            int fbad = *(--pre[c].ub(x));
                            if (fir.s < fbad) {
                                cout << "NE\n";
                            } else {
                                lo = 0, hi = sz(pts) - 1;            
                                ans = -1;
                                while (lo <= hi) {
                                    int mid = (lo + hi) / 2;
                                    pi curr = *(pts.fbo(mid));
                                    if (curr.s >= y) {
                                        hi = mid - 1;
                                        ans = mid;
                                    } else {
                                        lo = mid + 1;
                                    }
                                }
                                if (ans == -1) cout << "NE\n";
                                else {
                                    pi sec = *(pts.fbo(ans));
                                    int pbad = *(bad[c].lb(y));
                                    if (sec.s > pbad) cout << "NE\n";
                                    else {
                                        int xsid = fir.f, ysid = sec.f;
                                        if (*(bad[c ^ 1].lb(xsid)) >= ysid) {
                                            cout << "DA\n";
                                        } else {
                                            cout << "NE\n";
                                        }
                                    }
                                }
                            }
                        }                   
                    }
                }
            } else {
                pi r1 = mp(x, *bad[c].lb(x));
                pi r2 = mp(y, *bad[c2].lb(y));
                if (c) {
                    r1 = mp(*(--pre[c].ub(x)), x);
                    r2 = mp(*(--pre[c2].ub(y)), y);
                    swap(r1, r2);
                }
                 //dbg(r1, r2);
                if (has(r1, r2)) cout << "DA\n";
                else cout << "NE\n";
            }
        }
    }
}

