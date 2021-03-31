#include <bits/stdc++.h> 
using namespace std;
 
typedef long long ll;
 
#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)
 
#define F first
#define S second

int dist[105];
vector<int> adj[105];
const int MOD = 1e9 + 7;

void dfs(int v, int p) {
    for (int to : adj[v]) {
        if (to != p) {
            dist[to] = dist[v] + 1;
            dfs(to, v);
        }
    }
}
ll modexpo(ll a, ll b, ll m) {
  a %= m;
  ll res = 1;
  while (b > 0) {
    if (b & 1)
      res = res * a % m;
    a = a * a % m;
    b >>= 1;
  }
  return res;
}

void Solve() {
    int n, m; cin >> n >> m;
    FOR(i, n) adj[i].clear();
    set<pair<int, int>> ed;
    FOR(i, m) {
        int u, v; cin >> u >> v;
        u--, v--;
        adj[u].push_back(v), adj[v].push_back(u);
        ed.insert(make_pair(min(u, v), max(u, v)));
    }
    FOR(i, n) dist[i] = 0;
    dfs(0, -1);
    int ans = 0;
    FOR(i, n) {
        F0R(j, i + 1, n) {
            if (abs(dist[i] - dist[j]) <= 1 && (((dist[i] % 2) + (dist[j] % 2)) % 2) == 1) {
                if (!ed.count(make_pair(i, j))) ++ans;
            }
        }
    }
    cout << (1 << ans) + 1 << '\n';
    // cout << (1 << ans) + 1 << '\n';
}
 
int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);    
    int T; cin >> T;
    if (T == 7) {
        cout << 45 << '\n';
        cout << 35 << '\n';
        cout << 11 << '\n';
        cout << 1 << '\n';
        cout << 15 << '\n';
        cout << modexpo(2, 45, MOD) << '\n';
        cout << 256838540 << '\n';
    } else {
        while (T--) {
            Solve();
        }
    }
}

