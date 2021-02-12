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
    map<char, char> mp;
    mp['a'] = '4', mp['e'] = '3', mp['i'] = '1', mp['o'] = '0', mp['s'] = '5';
    string s; cin >> s;
    FOR(i, s.size()) {
        if (mp.find(s[i]) != mp.end()) s[i] = mp[s[i]];
    }
    cout << s << '\n';
}

