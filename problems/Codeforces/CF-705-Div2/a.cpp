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
    int T; cin >> T;
    while (T--) {
        int n, k; cin >> n >> k;
        vector<int> vals;
        F0R(i, 1, n + 1) {
            if (i >= ((k + 1) / 2) && i != k) {
                vals.push_back(i);
            }
        }
        cout << vals.size() << '\n';
        for (auto x : vals) cout << x << " ";
        cout << '\n';
    }
}
