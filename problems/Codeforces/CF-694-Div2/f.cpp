#include <bits/stdc++.h> 
using namespace std;
 
typedef long long ll;
 
#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)
 
#define F first
#define S second
 
const int MX = 300005;
 
bool vis[MX];
vector<int> adj[MX];
int anc[MX];
int col[MX];
 
void dfs(int v) {
    vis[v] = true;
    for (int to : adj[v]) {
        if (!vis[to]) {
            dfs(to);
        }
    }
}
 
void dfs_col(int v, int cc) {
    vector<int> nxt;
    for (int to : adj[v]) {
        if (col[to] == -1) {
            if (cc == 0) {
                col[to] = col[v] ^ 1;
                nxt.push_back(to);
            } else {
                col[to] = col[v] ^ 1;
                dfs_col(to, col[to]);
            }
        }
    }
    if (cc == 0) {
        for (int to : nxt) {
            dfs_col(to, col[to]);
        }
    }
}
 
void Solve() {
    int n, m; cin >> n >> m;
    FOR(i, n) {
        vis[i] = false; 
        adj[i].clear();
        anc[i] = -1;
        col[i] = -1;
    }
    FOR(i, m) {
        int u, v; cin >> u >> v;
        u--, v--;
        adj[u].push_back(v), adj[v].push_back(u);
    }
    int ccs = 0;
    FOR(i, n) {
        if (!vis[i]) {
            ++ccs;
            dfs(i);
        }
    }
    if (ccs > 1) cout << "NO\n";
    else {
        cout << "YES\n";
        col[0] = 0;
        dfs_col(0, 0);
        vector<int> res;
        FOR(i, n) if (col[i] == 0) res.push_back(i + 1);
        cout << res.size() << '\n';
        for (auto x : res) cout << x << " ";
        cout << '\n';
    }
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
