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
    int n; cin >> n;
    vector<pair<int, int>> vals;
    vector<bool> blocked(n), taken(n);
    vector<int> nxt(n, -1);
    FOR(i, n) {
        string s; cin >> s;
        array<int, 2> cval;
        cval[0] = 0, cval[1] = 0;
        int p = 0;
        FOR(j, s.size()) {
            if (s[j] == '-') {
                ++p; 
                continue;
            }
            cval[p] *= 10;
            cval[p] += (s[j] - '0');
        }
        if (cval[0] > cval[1]) swap(cval[0], cval[1]);
        vals.push_back({cval[0], cval[1]});
    }
    sort(vals.begin(), vals.end());
    vector<vector<pair<int, int>>> fr;
    auto gr = [&] (pair<int, int> &a, pair<int, int> &b) {
        if (b.F >= a.F && b.S >= a.S) return true;
        else return false;
    };
    for (auto x : vals) {
        bool found = false;
        FOR(j, fr.size()) {
            if (found || fr[j].empty()) continue;
            if (gr(fr[j].back(), x)) {
                fr[j].push_back(x);
                found = true;
            }
        }
        if (!found) {
            fr.resize(fr.size() + 1);
            fr[fr.size() - 1].push_back(x);
        }
    }
    cout << fr.size() << '\n';
    for (auto x : fr) {
        for (auto v : x) {
            cout << v.F << "-" << v.S << " ";
        }
        cout << '\n';
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

