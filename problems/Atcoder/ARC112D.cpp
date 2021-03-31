#include <bits/stdc++.h> 
#include <cstring>
using namespace std;
 
typedef long long ll;
 
#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)
 
#define F first
#define S second

int mp(int x, int c) {
    return 1000 * c + x;
}

vector<int> adj[2005];
bool vis[2005];

void dfs(int v) {
    vis[v] = true;
    for (int to : adj[v]) {
        if (!vis[to]) dfs(to);
    }
}

int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);    
    int n, m; cin >> n >> m;
    auto ad = [&] (int a, int b, int c, int d) {
        adj[mp(a, b)].push_back(mp(c, d)); 
        adj[mp(c, d)].push_back(mp(a, b)); 
    };
    auto add = [&] (int a, int b, int c, int d) {
        adj[mp(a, b)].push_back(mp(c, d)); 
    };
    FOR(i, m) add(i, 1, 0, 0);
    FOR(i, m) add(i, 1, n - 1, 0);
    FOR(i, n) add(i, 0, 0, 1);
    FOR(i, n) add(i, 0, m - 1, 1);
    FOR(i, n) {
        string s; cin >> s;
        FOR(j, m) {
            if (s[j] == '#') {
                ad(i, 0, j , 1);
            }
        }
    }
    int rcc = 0;
    FOR(i, n) {
        if (!vis[mp(i, 0)]) {
            dfs(mp(i, 0));
            ++rcc;
        }
    }
    memset(vis, false, sizeof(vis));
    int ccc = 0;
    FOR(i, m) {
        if (!vis[mp(i, 1)]) {
            dfs(mp(i, 1));
            ++ccc;
        }
    }
    cout << min(rcc - 1, ccc - 1) << '\n';
}

