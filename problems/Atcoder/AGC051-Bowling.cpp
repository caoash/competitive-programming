#include <bits/stdc++.h> 
using namespace std;

typedef long long ll;

#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)

#define F first
#define S second

int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int len = 1;
    pair<int, int> a = {len, len}, b = {len, 0}, c = {0, len};
    auto mul = [&] (pair<int, int> x, int cn) {
        return make_pair(x.F * cn, x.S * cn);
    };
    auto ad = [&] (pair<int, int> x, pair<int, int> y) {
        return make_pair(x.F + y.F, x.S + y.S);
    };
    set<pair<int, int>> res;
    FOR(i, 10) {
        FOR(j, 10) {
            FOR(k, 10) {
                pair<int, int> cur = ad(mul(b, 10 * i), mul(c, j));
                res.insert(cur);
            }
        }
    }
    cout << res.size() << '\n';
    for (auto x : res) {
        cout << x.F << " " << x.S << '\n';
    }
}

