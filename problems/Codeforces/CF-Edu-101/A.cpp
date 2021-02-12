#include <bits/stdc++.h> 
using namespace std;

typedef long long ll;

#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) for (int i = 0; i < n; i++)

#define F first
#define S second

void Solve() {
    string s; cin >> s;
    int sz = (int) s.size();
    if (sz % 2) {
        cout << "NO\n";
        return;
    }
    if (s[0] == ')' || s[sz - 1] == '(') {
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
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

