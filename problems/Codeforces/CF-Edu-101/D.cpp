#include <bits/stdc++.h> 
using namespace std;

typedef long long ll;

#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) for (int i = 0; i < n; i++)

#define F first
#define S second

void Solve() {
    int N; cin >> N;
    vector<pair<int, int>> ops;
    int use = (N > 8 ? 8 : 3);
    F0R(i, 3, N) {
        if (i != use) ops.push_back({i, N});
    }
    int M = N;
    if (use != N) {
        while (N > 1) {
            ops.push_back({M, use});
            N = ceil((double) N / (double) use);
        }
    }
    int orig = use;
    while (use > 1) ops.push_back({orig, 2}), use = (use + 1) / 2;
    cout << (int) ops.size() << '\n';
    for (auto x : ops) {
        cout << x.F << " " << x.S << '\n';
    }
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

