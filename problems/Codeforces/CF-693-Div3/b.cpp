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
    int oc = 0, tc = 0;
    int n; cin >> n;
    FOR(i, n) {
        int x; cin >> x;
        if (x == 1) oc++;
        else tc++;
    }
    int sum = (2 * tc) + oc;
    bool bad = false;
    if (sum % 2 == 1 || oc % 2 == 1) bad = true;
    if (tc % 2 == 1 && oc < 2) bad = true;
    cout << (bad ? "NO" : "YES") << '\n';
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

