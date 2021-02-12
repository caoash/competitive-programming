#include <bits/stdc++.h> 
using namespace std;

typedef long long ll;

#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)

#define F first
#define S second

const int MX = 500005;

vector<int> adj[MX];
int deg[MX];
int marked[MX][2];
int bad[MX];

int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    vector<pair<int, int>> eds;
    FOR(i, n - 1) {
        int u, v; cin >> u >> v;
        u--, v--;
        deg[u]++, deg[v]++;
        eds.push_back({u, v});
    }
    for (auto e : eds) {
        if (deg[e.F] > deg[e.S]) swap(e.F, e.S); 
        adj[e.F].push_back(e.S);
    }
    int q; cin >> q;
    int ccs = 1;
    FOR(tc, q) {
        int x; cin >> x;
        int nod = abs(x) - 1, type = (x > 0);
        if (type) {
            marked[nod][0] = 0;
            for (int to : adj[nod]) marked[nod][0] += bad[to];
            ccs += (deg[nod] - (marked[nod][0] + marked[nod][1]) - 1);
            for (int to : adj[nod]) marked[to][1]++;
            bad[nod] = 1;
        } else {
            marked[nod][0] = 0;
            for (int to : adj[nod]) marked[nod][0] += bad[to];
            ccs -= (deg[nod] - (marked[nod][0] + marked[nod][1]) - 1);
            for (int to : adj[nod]) marked[to][1]--;
            bad[nod] = 0;
        }
        cout << ccs << '\n';
    }
}

