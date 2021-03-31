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
const int MAGIC = 100;

vector<int> adj[MX];
int dist[MAGIC][MX];
bool vis[MX];
 
int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);    
    srand(69420);
    int n, m, p; cin >> n >> m >> p;
    FOR(i, m) {
        int u, v; cin >> u >> v;
        u--, v--;
        adj[u].push_back(v), adj[v].push_back(u);
    }
    vector<int> nods;
    FOR(i, n) nods.push_back(i);
    random_shuffle(nods.begin(), nods.end());
    int num = min(MAGIC, n);
    auto bfs = [&] (int src) {
        int s = nods[src];
        queue<int> q;
        FOR(i, n) {
            vis[i] = false;
            dist[src][i] = 1e9;
        }
        q.push(s);
        dist[src][s] = 0;
        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            if (!vis[curr]) {
                for (int to : adj[curr]) {
                    if (!vis[to]) {
                        if (dist[src][to] > dist[src][curr] + 1) {
                            dist[src][to] = dist[src][curr] + 1; 
                            q.push(to);
                        }
                    }
                }
                vis[curr] = true;
            }
        }
    };
    FOR(i, num) {
        bfs(i);
    }
    FOR(i, p) {
        int u, v; cin >> u >> v;
        u--, v--;
        int ans = 1e9;
        FOR(j, num) {
            ans = min(ans, dist[j][u] + dist[j][v]);
        }
        cout << ans << '\n';
    }
}


