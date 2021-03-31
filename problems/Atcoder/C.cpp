#include <bits/stdc++.h> 
using namespace std;
 
typedef long long ll;
 
#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)
 
#define F first
#define S second

int psum[200005][26];
 
int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);    
    string s; cin >> s;
    FOR(i, s.size()) {
        FOR(j, 26) {
            psum[i][j] = (i == 0 ? 0 : psum[i - 1][j]);
        }
        psum[i][s[i] - 'a']++;
    }
    auto qry = [&] (int l, int r, int c) {
        if (l > r) return 0;
        if (l == 0) return psum[r][c];
        else return psum[r][c] - psum[l - 1][c];
    };
    ll ans = 0;
    char prev = '$';
    int loc = s.size();
    F0RD(i, 1, s.size()) {
        if (s[i] == s[i - 1] && (i == 1 || s[i] != s[i - 2])) {
            if (s[i] != prev) {
                ans += (s.size() - i - 1);
            }
            else {
                ans += (loc - i - 1);
            }
            ans -= qry(i + 1, loc - 1, s[i] - 'a');
            prev = s[i], loc = i;
        }
    }
    cout << ans << '\n';
}

