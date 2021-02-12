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
    int L; cin >> L;
    int N = 1;
    vector<array<int, 3>> eds;
    int nods = 2;
    eds.push_back({1, 2, 0});
    auto dub = [&] () {
        vector<array<int, 3>> neds;
        for (auto x : eds) neds.push_back({x[0] + 1, x[1] + 1, 2 * x[2]});
        ++nods;
        neds.push_back({1, 2, 0});
        neds.push_back({1, 2, 1});
        N *= 2;
        swap(eds, neds);
    };
    auto ad = [&] () {
        eds.push_back({1, nods, N});
        ++N;
    };
    vector<int> ops;
    int dubc = 0;
    while (L > 1) {
        if (L % 2 == 0 && dubc < 18) {
            ops.push_back(0);
            L /= 2;
            ++dubc;
        } else {
            ops.push_back(1);
            L--;
        }
    }
    reverse(ops.begin(), ops.end());
    for (auto x : ops) {
        if (x) ad();
        else dub();
    }
    cout << nods << " " << eds.size() << '\n';
    for (auto x : eds) {
        cout << x[0] << " " << x[1] << " " << x[2] << '\n';
    }
}

