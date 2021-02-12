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
vector<int> adj[MX], gr[MX];
int dir[MX], anc[MX];
bool vis[MX];
vector<int> ord;

void dfs(int v, int p) {
    int col = dir[v];
    for (int to : adj[v]) {
        if (to != p) {
            dir[to] = col;
            anc[to] = v;
            col ^= 1;
        }
    }
    for (int to : adj[v]) {
        if (to != p) dfs(to, v);
    }
}

void dfs_ord(int v) {
    vis[v] = true;
    for (int to : gr[v]) {
        if (!vis[to]) {
            dfs_ord(to);
        }
    }
    ord.push_back(v);
}

int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    FOR(i, n - 1) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dir[0] = 0;
    dfs(0, -1);
    FOR(i, n) { 
        if (dir[i] == 0) {
            gr[i].push_back(anc[i]);
        } else {
            gr[anc[i]].push_back(i);
        }
    }
    FOR(i, n) {
        if (!vis[i]) dfs_ord(i);
    }
    reverse(ord.begin(), ord.end());
    for (auto x : ord) {
        cout << x << " ";
    }
    cout << '\n';
}

