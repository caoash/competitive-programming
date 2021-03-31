#include <bits/stdc++.h> 
using namespace std;
 
typedef long long ll;
 
#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)
 
#define F first
#define S second

bool adj[2005][2005];
 
int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);    
    int n, m; cin >> n >> m;
    FOR(i, m) {
        int u, v; cin >> u >> v;
        u--, v--;
        adj[u][v] = true, adj[v][u] = true;
    }
    int ans = -1;
    int best = 0;
    FOR(mask, (1 << n)) {
        int num = 0;
        FOR(i, n) {
            int fir = (mask & (1 << i)) > 0;
            int deg = 0;
            FOR(j, n) {
                if (adj[i][j]) {
                    int sec = (mask & (1 << j)) > 0;
                    if (fir == sec) ++deg;
                }
            }
            if (deg % 2 == 0) ++num;
        }
        if (num > ans) ans = num, best = mask;
    }
    cout << ans << '\n';
    FOR(i, n) {
        if (best & (1 << i)) cout << 1;
        else cout << 2;
        if (i != n - 1) cout << " ";
    }
    cout << '\n';
}

