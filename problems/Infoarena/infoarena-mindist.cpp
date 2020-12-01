/*
 * You can do manhattan distance transformation and then maintain with a segtree that stores a set of y's for each range of x's.
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

#ifdef mikey 
using namespace output;
#else
using namespace output;
#define dbg(x...)
#endif

const int MX = 150005;
const int MOD = (int) (1e9 + 7);
const ll INF = (ll) 1e18;
const int OFFSET = 50000;

set<int> tr[4 * MX];

void update(int v, int l, int r, int x, int y) {
    if (l > x || r < x) {
        return;
    }
    tr[v].insert(y);
    if (l != r) {
        int m = (l + r) / 2;
        update(2 * v + 1, l, m, x, y);
        update(2 * v + 2, m + 1, r, x, y);
    }
}

bool ok = false;

bool query(int v, int l, int r, int xl, int xr, int yl, int yr) {
    if (l > xr || r < xl) {
        return false;
    } else if (l >= xl && r <= xr) {
        auto it = tr[v].lb(yl);
        if (it != tr[v].end()) {
            if (*it <= yr) {
                ok = true;
                return true;
            }
        }
        return false;
    } else {
        int m = (l + r) / 2;
        if (ok) return true;
        else return query(2 * v + 1, l, m, xl, xr, yl, yr) || query(2 * v + 2, m + 1, r, xl, xr, yl, yr);
    }
}

int main(){
    freopen("mindist.in", "r", stdin);
    freopen("mindist.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        x--, y--;
        int a = (x + y), b = (x - y);
        a += OFFSET, b += OFFSET;
        int lo = 1, hi = (int)1e5 + OFFSET;
        int ans = 0;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            int xl = max(0, a - mid), xr = min((int)1e5 + OFFSET, a + mid);
            int yl = max(0, b - mid), yr = min((int)1e5 + OFFSET, b + mid);
            ok = false;
            if (query(0, 0, (int)1e5 + OFFSET, xl, xr, yl, yr)) {
                hi = mid - 1;
                ans = mid;
            } else {
                lo = mid + 1;
            }
        }
        cout << ans << '\n';
        update(0, 0, (int)1e5 + OFFSET, a, b);
    }
}

