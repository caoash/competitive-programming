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

const int MX = 50005;

vector<int> adj[MX];
vector<int> rev[MX];
vector<pair<int, int>> ed;
int scc_num[MX], scc_sz[MX];
set<int> scc_adj[MX];
bool used[MX];
vector<int> ord;
int dp[MX];

void dfs1(int v) {
    used[v] = true;
    for (int to : adj[v]) {
        if (!used[to]) dfs1(to);
    }
    ord.push_back(v);
}

void dfs2(int v, int cnt) {
    used[v] = true;
    scc_num[v] = cnt;
    scc_sz[cnt]++;
    for (int to : rev[v]) {
        if (!used[to]) dfs2(to, cnt);
    }
}

void dfs3(int v) {
    used[v] = true;
    for (int to : scc_adj[v]) {
        if (!used[to]) {
            dfs3(to);
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
    int n, m; cin >> n >> m;
    FOR(i, m) {
        int u, v; cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        rev[v].push_back(u);
        ed.push_back({u, v});
    }
    FOR(i, n) {
        if (!used[i]) dfs1(i);
    }
    memset(used, false, sizeof(used));
    reverse(ord.begin(), ord.end());
    int c = 0;
    for (auto x : ord) {
        if (!used[x]) dfs2(x, ++c);
    }
    for (auto e : ed) {
        scc_adj[scc_num[e.F]].insert(scc_num[e.S]);
    }
    memset(used, false, sizeof(used));
    ord.clear();
    F0R(i, 1, c + 1) {
        if (!used[i]) dfs3(i);
    }
    for (auto x : ord) {
        for (int to : scc_adj[x]) {
            dp[x] += dp[to];
        }
        dp[x] += scc_sz[x];
    }
    FOR(i, n) {
        cout << dp[scc_num[i]] - 1 << '\n';
    }
}

