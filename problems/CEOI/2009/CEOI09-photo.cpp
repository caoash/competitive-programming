/*
 * Make observations about the structure of the answer (which I started, but I could have gotten more specific).
 *
 * Then, you can see they are either disjoint or nested, allowing a nice (but not that nice to implement) DP to fall into place.
 *
 * Let dp[left bound][right bound][bottom bound] = minimum number of rectangles needed to cover.
 *
 * See editorial for more details.
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

const int MX = 105;
const int MOD = (int) (1e9 + 7);
const ll INF = (ll) 1e18;

int n, a;
vector<pi> pts;
int dp[MX][MX][MX];
map<int, int> xv, yv;
map<int, int> xc, yc;

int go(int l, int r, int h) {
    if (dp[l][r][h] != INT_MAX) {
        return dp[l][r][h];
    } else if (l == r) {
        return dp[l][r][h] = 1;
    } else if (r < l) {
        return dp[l][r][h] = 0;   
    } else {
        vi valid;
        vi vex;
        for (int i = 0; i < sz(pts); i++) {
            auto sp = pts[i];
            if (sp.f >= xc[l] && sp.f <= xc[r] && sp.s >= yc[h]) {
                valid.pb(i);
                vex.pb(sp.f);
            }
        }
        sort(all(vex));
        vex.rsz(unique(all(vex)) - vex.begin());
        for (int i = 0; i < sz(vex) - 1; i++) {
             int to = xv[vex[i]];
             int sec = xv[vex[i + 1]];
             if (to >= l && sec <= r) {
                 int ffs = go(l, to, h);
                 int ffc = go(sec, r, h);
                 dp[l][r][h] = min(dp[l][r][h], ffs + ffc);
             }
        }
        int need = a / (xc[r] - xc[l]);
        int mn = INT_MAX;
        int nk = -1;
        for (int i = 0; i < sz(valid); i++) {
            int x = valid[i];
            if (pts[x].s > need && pts[x].s < mn) {
                mn = pts[x].s, nk = yv[pts[x].s];
            }
        }
        int ni = -1, nj = -1;
        int mi = INT_MAX, mj = -1;
        for (int i = 0; i < sz(valid); i++) {
            int x = valid[i];
            if (pts[x].s >= yc[nk]) {
                if (pts[x].f < mi) mi = pts[x].f, ni = xv[pts[x].f];
                if (pts[x].f > mj) mj = pts[x].f, nj = xv[pts[x].f];
            }
        }
        if (ni >= 0 && nj >= 0 && nk >= 0 && ni < sz(xv) && nj < sz(xv) && nk < sz(yv)) {
            dp[l][r][h] = min(dp[l][r][h], 1 + go(ni, nj, nk));
        } else {
            if (valid.empty()) dp[l][r][h] = 0;
            else dp[l][r][h] = 1;
        }
        return dp[l][r][h];
    }
}

void solve(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> a;
    set<int> xs, ys;
    pts.clear();
    for (int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        pts.pb(mp(x, y));
        xs.insert(x), ys.insert(y);
    }
    xv.clear(), xc.clear();
    yv.clear(), yc.clear();
    int cnt = 0;
    for (auto x : xs) xv[x] = cnt, xc[cnt] = x, cnt++;
    cnt = 0;
    for (auto y : ys) yv[y] = cnt, yc[cnt] = y, cnt++;
    for (int i = 0; i < MX; i++) 
    for (int j = 0; j < MX; j++)
    for (int k = 0; k < MX; k++) {
        dp[i][j][k] = INT_MAX;
    }
    cout << go(0, sz(xv) - 1, 0) << '\n';
}

int main() {
    solve(); 
}

