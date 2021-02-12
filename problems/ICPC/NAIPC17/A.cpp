#include <bits/stdc++.h> 
using namespace std;

typedef long long ll;

#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)

#define F first
#define S second

ll dp[305][305 * 305];

struct Paren {
    int a, b, len;
    bool operator<(const Paren &o) {
        if (a > 0 && o.a <= 0) return true;
        else if (o.a > 0 && a <= 0) return false;
        else if (a > 0 && o.a > 0) {
            return (b < o.b);
        } else {
            return (a + b) > (o.a + o.b);
        }
    };
};

int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n; 
    vector<Paren> vals(n);
    FOR(i, n) {
        string s; cin >> s;
        int bal = 0, mn = 0;
        FOR(j, (int) s.size()) {
            bal += (s[j] == '(' ? 1 : -1);
            mn = min(mn, bal);
        }
        mn *= -1;
        vals[i].a = bal, vals[i].b = mn, vals[i].len = (int) s.size();
    }
    sort(vals.begin(), vals.end());
/*
for (auto x : vals) {
cout << "i, vals: " << " " << x.F.F << " " << x.F.S << '\n';
}
*/
    FOR(i, n + 1) FOR(j, 300 * n + 1) dp[i][j] = -1e18;
    dp[0][0] = 0;
    FOR(i, n) FOR(j, 300 * n + 1) {
        dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]); 
        if (j >= vals[i].b) {
            dp[i + 1][j + vals[i].a] = max(dp[i + 1][j + vals[i].a], dp[i][j] + vals[i].len);
        }
    };
    cout << dp[n][0] << '\n';
}

