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
    ll n, m; cin >> n >> m;
    int k; cin >> k;
    map<ll, int> row, col;
    FOR(i, k) {
        ll x, y; cin >> x >> y;
        row[x] ^= 1;
        col[y] ^= 1;
    }
    vector<ll> brow, bcol;
    for (auto x : row) {
        if (x.S) brow.push_back(x.F);
    }
    for (auto x : col) {
        if (x.S) bcol.push_back(x.F);
    }
    vector<pair<ll, ll>> ans;
    while (!bcol.empty() && !brow.empty()) {
        ans.push_back({brow.back(), bcol.back()});
        bcol.pop_back();
        brow.pop_back();
    }
    while (!bcol.empty()) {
        ans.push_back({1, bcol.back()});
        bcol.pop_back();
    }
    while (!brow.empty()) {
        ans.push_back({brow.back(), 1});
        brow.pop_back();
    }
    cout << ans.size() << '\n';
    for (auto x : ans) {
        cout << x.F << " " << x.S << '\n';
    }
}

/*
 * 1 1
 * 1 3
 * 2 1
 *
 * X X O
 * O X O
 * X O O
 *
 * 0 1 1
 * 0 0 0
 */
