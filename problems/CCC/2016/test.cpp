#include <bits/stdc++.h> 
using namespace std;

typedef long long ll;

#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) for (int i = 0; i < n; i++)

#define F first
#define S second
#define pi pair<int, int>

int main(){
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    vector<pi> vals;
    for (int i = 0; i < 1e6; i++) {
        vals.pb(mp(rand() % 100, rand() % 100));
    }
}

