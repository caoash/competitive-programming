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
    vector<string> ret;
    ret.push_back(" @@@   @@@ ");
    ret.push_back("@   @ @   @");
    ret.push_back("@    @    @");
    ret.push_back("@         @");
    ret.push_back(" @       @ ");
    ret.push_back("  @     @  ");
    ret.push_back("   @   @   ");
    ret.push_back("    @ @    ");
    ret.push_back("     @     ");
    int n; cin >> n;
    FOR(i, n) {
        for (auto x : ret) cout << x << '\n';
    }
}

