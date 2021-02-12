#include <bits/stdc++.h> 
using namespace std;

typedef long long ll;

#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)

#define F first
#define S second

int dp[5281];

int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int s; cin >> s;
    int n; cin >> n;
    vector<int> a(n);
    FOR(i, n) cin >> a[i];
    FOR(i, s + 1) dp[i] = 1e9;
    dp[0] = 0;
    FOR(j, s + 1) F0R(i, 1, n + 1) {
        if (j - a[i - 1] >= 0) dp[j] = min(dp[j], dp[j - a[i - 1]] + 1);
    }
    if (dp[s] == 1e9) printf("Roberta acknowledges defeat.");
    else printf("Roberta wins in %d strokes.", dp[s]);
}

