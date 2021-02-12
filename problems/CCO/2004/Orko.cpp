#include <bits/stdc++.h> 
using namespace std;

typedef long long ll;

#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)

#define F first
#define S second

const int MX = 10;

int mp(char c, int v) {
    string s = "RYGB";
    int ind = -1;
    FOR(i, 4) if (s[i] == c) ind = i;
    return 5 * ind + (v - 1);
}

pair<int, int> rev(int x) {
    return make_pair(x / 5, x % 5);
}

int dp[(1 << MX)][(1 << MX)][MX][2];
bool used[MX];

void Solve(string s) {
    vector<int> fir;
    vector<int> sec;
    for (int i = 0; i < s.size(); i += 3) {
        int cv = mp(s[i], s[i + 1] - '0');
        fir.push_back(cv);
    }
    FOR(i, MX) {
        if (!used[i]) sec.push_back(i);
    }
    dp[0][0] = 0;
    int n = s.size();
    auto comp = [&] (int i, int j) {
        pair<int, int> &fr = rev(i);
        pair<int, int> &sr = rev(j);
        if (fr.F != sr.F) return 1;
    };
    FOR(mask1, (1 << MX)) {
        FOR(mask2, (1 << MX)) {
            FOR(i, MX) {
                // prev card played
                FOR(turn, 2) {
                    int cmask = (turn ? mask2 : mask1);
                    int omask = (turn ? mask1 : mask2);
                    if (omask & (1 << i)) continue;
                    int fmask = (turn ? mask1 : (mask1 | (1 << i)));
                    int smask = (turn ? (mask2 | (1 << i)) : mask2);
                    bool has = false;
                    vector<int> &cvec = (turn ? sec : fir);
                    vector<int> &ovec = (turn ? fir : sec);
                    pair<int, int> &prv = rev(ovec[i]);
                    FOR(j, MX) {
                        pair<int, int> &cur = rev(cvec[j]);
                        if (cur.F == prv.F) has = true;
                    }
                    FOR(j, MX) {
                        pair<int, int> &cur = rev(cvec[j]);
                        if (has && cur.F != prv.F) continue;
                        dp[fmask][smask][j][turn] = max(dp[fmask][smask][j][turn], dp[mask1][mask2][i][turn ^ 1] + comp(cvec[j], ovec[i]));
                    }
                }
            }
        }
    }
}

int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    string s;
    while (cin >> s) {
        if (s[0] != '*') Solve(s);
    }
}

