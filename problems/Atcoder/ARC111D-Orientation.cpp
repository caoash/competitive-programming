#include <bits/stdc++.h> 
using namespace std;

typedef long long ll;

#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)

#define F first
#define S second

const int MX = 100005;

vector<int> adj[MX];

int c[MX];
int anc[MX], dep[MX];
bool vis[MX];

void dfs(int v) {
    vis[v] = true;
    for (int to : adj[v]) {
        if (c[to] != c[v]) continue;
        if (!vis[to]) {
            anc[to] = v;
            dep[to] = dep[v] + 1;
            dfs(to);
        }
    }
}

int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m; cin >> n >> m;
    vector<pair<int, int>> eds;
    FOR(i, m) {
        int u, v; cin >> u >> v;
        u--, v--;
        adj[u].push_back(v), adj[v].push_back(u);
        eds.push_back({u, v});
    }
    FOR(i, n) cin >> c[i];
    FOR(i, n) {
        if (!vis[i]) dfs(i);
    }
    for (auto e : eds) {
        if (c[e.F] > c[e.S]) {
            cout << "->" << '\n';
        } else if (c[e.F] < c[e.S]) {
            cout << "<-" << '\n';
        } else {
            bool cng = false;
            if (dep[e.F] > dep[e.S]) {
                swap(e.F, e.S);
                cng = true;
            }
            int res = 0;
            if (anc[e.S] == e.F) {
                res = 1;
            } 
            if (cng) res ^= 1;
            cout << (res ? "->" : "<-") << '\n';
        }
    }
}

