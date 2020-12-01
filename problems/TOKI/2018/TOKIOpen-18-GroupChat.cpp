/*
 * Do reduction (x + y, x - y) then you can check two squares that contain all points with bsearch.
 */

#include <bits/stdc++.h> 
#include "group.h"
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
using pl = pair<ll, ll>;
#define f first
#define s second
#define mp make_pair

const int MX = 200005;
const int MOD = (int) (1e9 + 7);
const ll INF = (ll) 1e18;

int getMinimumDelay(int N, vi X, vi Y) {
    vector<pl> pts;
    pl bot = mp(INF, INF);
    pl top = mp(-INF, -INF);
    for (int i = 0; i < N; i++) {
        ll a = (X[i] + Y[i]), b = (X[i] - Y[i]);
        pts.pb(mp(a, b));
        bot.f = min(bot.f, a), bot.s = min(bot.s, b);
        top.f = max(top.f, a), top.s = max(top.s, b);
    }
    ll lo = 0, hi = 2e9;
    auto has = [&] (array<ll, 4> rect, pl pnt) {
        return pnt.f >= rect[0] && pnt.s >= rect[1] && pnt.f <= rect[2] && pnt.s <= rect[3];
    };
    ll ret = 0;
    while (lo <= hi) {
        ll mid = (lo + hi) / 2;
        array<ll, 4> r1, r2, r3, r4;
        r1[0] = bot.f, r1[1] = bot.s;
        r1[2] = r1[0] + mid, r1[3] = r1[1] + mid;
        r2[0] = top.f - mid, r2[1] = top.s - mid;
        r2[2] = top.f, r2[3] = top.s;
        r3[0] = bot.f, r3[1] = top.s - mid;
        r3[2] = bot.f + mid, r3[3] = top.s;
        r4[0] = top.f - mid, r4[1] = bot.s;
        r4[2] = top.f, r4[3] = bot.s + mid;
        bool ok = true;
        bool ok2 = true;
        for (int i = 0; i < N; i++) {
            pl cur = pts[i];
            ok &= (has(r1, cur) || has(r2, cur));
            ok2 &= (has(r3, cur) || has(r4, cur));
        }
        if (ok || ok2) {
            hi = mid - 1;
            ret = mid;
        } else {
            lo = mid + 1;
        } 
    }
    return ret;
}
