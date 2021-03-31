#include <bits/stdc++.h> 
using namespace std;
 
typedef long long ll;
 
#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)
 
#define F first
#define S second

void Solve() {
    int n, m; cin >> n >> m;
    vector<int> adj[n];
    FOR(i, m) {
        int u, v; cin >> u >> v;
        u--, v--;
        adj[u].push_back(v), adj[v].push_back(u);
    }
    if (bi()) {
        cout << n - 1 << '\n';
        return;
    }
    if (n <= 5) {

    } else {
        auto bi = [&] () {
            bool res = true;
            queue<int> q;
            vector<int> col(n, -1);
            q.push(0);
            col[0] = 0;
            while (!q.empty()) {
                int v = q.front();
                q.pop();
                for (int to : adj[v]) {
                    if (col[to] == -1) {
                        col[to] = col[v] ^ 1;
                        q.push(to);
                    } else {
                        if (col[to] == col[v]) {
                            res = false;
                        }
                    }
                }
            }
            return res;
        };
        cout << m << '\n';
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

