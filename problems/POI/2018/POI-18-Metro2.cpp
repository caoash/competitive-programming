#include <bits/stdc++.h> 
using namespace std;

typedef long long ll;

#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)

#define F first
#define S second

const int MX = 3000005;

vector<int> adj[MX];
int deg[MX], done[MX];

int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, k; cin >> n >> k;
    FOR(i, n - 1) {
        int u, v; cin >> u >> v;
        u--, v--;
        deg[u]++, deg[v]++;
        adj[u].push_back(v), adj[v].push_back(u);
    }
    vector<int> del;
    vector<int> nxt;
    FOR(i, n) if (deg[i] == 1) del.push_back(i);
    int ans = 0;
    while (!del.empty()) {
        if (del.size() <= k) {
            break;
        }
        ++ans;
        nxt.clear();
        for (auto curr : del) {
            for (int to : adj[curr]) {
                if (!done[to]) {
                    deg[to]--;
                    if (deg[to] == 1) nxt.push_back(to);
                }
            }
            done[curr] = true;
        }
        del = nxt;
    }
    if (del.size() == 1) {
        int x = del[0];
        for (int i = 0; i < n; i++) {
            if (x != i) {
                del.push_back(i);
                break;
            }
        }
    }
    cout << ans << " " << del.size() << '\n';
    for (auto x : del) cout << x + 1 << " ";
}

