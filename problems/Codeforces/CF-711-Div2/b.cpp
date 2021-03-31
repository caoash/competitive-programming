#include <bits/stdc++.h> 
using namespace std;
 
typedef long long ll;
 
#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)
 
#define F first
#define S second

void Solve() {
    int n, W; cin >> n >> W;
    vector<int> w(n);
    multiset<int> vals;
    FOR(i, n) {
        cin >> w[i];
        vals.insert(w[i]);
    }
    int ans = 0;
    while (!vals.empty()) {
        ++ans;
        auto best = --vals.end();
        int cur = *best; 
        while (cur > 0) {
            if (vals.count(cur)) {
                vals.erase(vals.find(cur));
            }
            cur /= 2;
        }
    }
    cout << ans << '\n';
}
 
int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);    
    int T; cin >> T;
    while (T--) {
        Solve();
    }
}

