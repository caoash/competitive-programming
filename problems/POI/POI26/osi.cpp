#include <bits/stdc++.h> 
using namespace std;
 
typedef long long ll;
 
#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)
 
#define F first
#define S second

const int MX = 1000005;

vector<pair<int, int>> adj[MX];
pair<int, int> anc[MX];
int dep[MX], tin[MX], tout[MX];
map<pair<int, int>, int> cnt;
bool vis[MX];
int timer = 0;
int bridges = 0;

void dfs(int v, int p) {
    vis[v] = true;
    tin[v] = tout[v] = timer++;
    for (pair<int, int> &to : adj[v]) {
        if (to.F == p) continue;
        if (!vis[to.F]) {
            dep[to.F] = dep[v] + 1;
            anc[to.F] = make_pair(v, to.S);
            dfs(to.F, v);
            tout[v] = min(tout[v], tout[to.F]);
            if (tout[to.F] > tin[v] && cnt[{min(to.F, v), max(to.F, v)}] == 1) {
                ++bridges;
            }
        } else {
            tout[v] = min(tout[v], tin[to.F]);
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
    vector<pair<int, int>> ed;
    FOR(i, m) {
        int u, v; cin >> u >> v;
        u--, v--;
        adj[u].push_back({v, i}), adj[v].push_back({u, i});
        ed.push_back(make_pair(u, v));
        cnt[{min(u, v), max(u, v)}]++;
    }
    int ccs = 0;
    FOR(i, n) {
        if (!vis[i]) {
            ++ccs;
            dfs(i, - 1);
        }
    }
    cout << ccs + bridges << '\n';
    FOR(i, m) {
        int a = ed[i].F, b = ed[i].S; 
        bool dir = true;
        if (dep[a] > dep[b]) {
            swap(a, b);
            dir ^= 1;
        }
        if (anc[b].S != i) {
            dir ^= 1;
        }
        cout << (dir ? '>' : '<');
    }
    cout << '\n';
}

