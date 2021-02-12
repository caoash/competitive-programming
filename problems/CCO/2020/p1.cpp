#include <bits/stdc++.h> 
using namespace std;

typedef long long ll;
typedef long double ld;

#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)

#define F first
#define S second

const ll INF = 1e18;

struct Line {
    ld m, b;
    Line (int x, ld slope) {
        m = slope; 
        b = (slope * (double) x * -1.0);
    }
    ld solve(int y) {
        return (ld) (y - b) / m;
    }
};

ll ret[100005];
const double EPS = 1e-9;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    vector<pair<int, int>> vals;
    ll l, r, y; cin >> l >> r >> y;
    FOR(i, n) {
        ld x, v, h; cin >> x >> v >> h;
        ld slope = (ld) (v / h);
        // dbg(v, h, slope);
        Line* cur = new Line(x, slope);
        ld pos = cur->solve(y);
        // dbg(pos);
        vals.push_back({floor(pos - EPS), 1});
        cur = new Line(x, -slope);
        pos = cur->solve(y);
        // dbg(pos);
        vals.push_back({ceil(pos + EPS), 0});
    }
    ll ans = 0;
    pair<ll, int> prev = {-INF, 0};
    vals.push_back({l, -2});
    vals.push_back({r, -1});
    sort(vals.begin(), vals.end());
    for (auto x : vals) {
        // dbg(x, prev, ans);
        if (x.S == -2) {
            prev = {x.F, 0};
            continue;
        } else if (x.S == -1) {
            if (prev.F >= l && prev.F <= r) ret[ans] += (x.F - prev.F + (prev.S ^ 1));
            prev = {x.F, 1};
            continue;
        } else if (x.S == 0 && prev.S == 0) {
            if (x.F >= l && x.F <= r && prev.F >= l && prev.F <= r) ret[ans] += x.F - prev.F;
            ++ans;
        } else if (x.S == 1 && prev.S == 0) {
            if (x.F >= l && x.F <= r && prev.F >= l && prev.F <= r) ret[ans] += x.F - prev.F + 1;
            --ans;
        } else if (x.S == 0 && prev.S == 1) {
            if (x.F >= l && x.F <= r && prev.F >= l && prev.F <= r) ret[ans] += x.F - prev.F - 1;
            ++ans;
        } else if (x.S == 1 && prev.S == 1) {
            if (x.F >= l && x.F <= r && prev.F >= l && prev.F <= r) ret[ans] += x.F - prev.F;
            --ans;
        }
        prev = x;
    }
    // if (prev.F >= l && prev.F <= r) ret[ans] += r - prev.F;
    ll sum = 0;
    FOR(i, n + 1) {
        sum += ret[i];
        cout << sum << '\n';
    }
}

