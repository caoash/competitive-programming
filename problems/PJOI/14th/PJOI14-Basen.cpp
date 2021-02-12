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
    int n; cin >> n;
    vector<int> a(n);
    FOR(i, n) cin >> a[i];
    bool dir = false;
    int ans = 0;
    FOR(i, n - 1) {
        if (!dir && a[i + 1] < a[i]) {
            dir = true;
            ++ans;
        } else if (dir && a[i + 1] > a[i]) {
            dir = false;
            ++ans;
        }
    }
    cout << ans + 1 << '\n';
}

