#include <bits/stdc++.h> 
using namespace std;
 
typedef long long ll;
 
#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)
 
#define F first
#define S second

ll dp[5005][32];

void Solve() {
    int n; cin >> n;
    vector<ll> a(n), b(n);
    FOR(i, n) cin >> a[i];
    FOR(i, n) cin >> b[i];
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

/*
 * iq strictly increases
 *
 * 0001
 * 0010
 * 0100
 *
 * basically, jump sizes just need to be larger than previous jump
 *
 * |2^i - 2^j| increasing
 *
 * claim: jump wont consist of more than 32 jumps
 * proof: hib increases each time, because look at the hib of your previous jump, new jump needs to be greater
 *
 *
 * 0001
 * 0100
 *
 * 0011
 *
 * 10000
 *
 * 00100
 *
 * claim: problem is equivalent if you increase ci by 1
 *
 * then we deal with some prefix of 1s, which is nicer
 *
 * claim: it always looks like a subarray of 1s
 *
 * 000001
 * 000011
 * 000111
 * 001111
 * 011111
 *
