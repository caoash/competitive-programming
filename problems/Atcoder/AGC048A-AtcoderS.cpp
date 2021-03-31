#include <bits/stdc++.h> 
#include <cassert>
using namespace std;
 
typedef long long ll;
 
#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)
 
#define F first
#define S second

const string need = "atcoder";

void Solve() {
    string s; cin >> s;
    if (s > need) {
        cout << 0 << '\n';
        return;
    }
    int ans = 1e9;
    assert((s[0] == 'a'));
    if (s[0] == 'a') {
        if (s.size() > 1) {
            if (s[1] == 'a') {
                F0R(i, 2, s.size()) {
                    if (s[i] > 'a') {
                        ans = min(ans, i);
                    }
                    if (s[i] > 't') {
                        ans = min(ans, abs(i - 1));
                    }
                }
            } else {
                ans = 1;
            }
        }
    } 
    if (ans == 1e9) ans = -1;
    cout << ans << '\n';
}
 
int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    int T; cin >> T; 
    while (T--) {
        Solve();
    }
}

