#include <bits/stdc++.h> 
using namespace std;

typedef long long ll;

#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)

#define F first
#define S second

const int MX = 50005;
const int MOD = (int) (1e9 + 7);

struct Graph {
    // int ways[N];
    vector<vector<int>> adj;
    vector<int> dist[2];
    vector<int> vis[2];
    int siz;

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void init(int n) {
        siz = n;
        adj.resize(n);
        FOR(j, 2) {
            dist[j].resize(n);
            vis[j].resize(n);
        }
    }

    void bfs(int s) {
        FOR(i, siz) {
            FOR(j, 2) {
                dist[j][i] = 1e9;
                vis[j][i] = false;
            }
        }
        queue<pair<int, int>> qq;
        qq.push({s, 0});
        dist[0][s] = 0;
        while (!qq.empty()) {
            pair<int, int> curr = qq.front();
            qq.pop();
            for (int to : adj[curr.F]) {
                if (!vis[curr.S ^ 1][to]) {
                    if (dist[curr.S ^ 1][to] > dist[curr.S][curr.F] + 1) {
                        dist[curr.S ^ 1][to] = dist[curr.S][curr.F] + 1;
                        qq.push({to, curr.S ^ 1});
                    }
                }
            }
            vis[curr.S][curr.F] = true;
        }
        /*
        FOR(i, N) {
            if (dist[i] != 1e9 && dist[i] != 0) {
                ways[dist[i]]++;
            }
        }
        */
    }
};

vector<Graph> gs;
vector<int> ni;
int K;
ll ans = 0;
ll dp[305][305][305];

/*
void Solve(int it, vector<int> &nods) {
    if (it < K) {
        FOR(i, ni[it]) {
            nods.push_back(i);
            Solve(it + 1, nods);
            nods.pop_back();
        }
    } else {
        ll clen = 1e9;
        FOR(p, 2) {
            ll big = -1;
            FOR(i, nods.size()) {
                ll best = gs[i].dist[p][nods[i]];
                big = max(big, best);
            }
            clen = min(clen, big);
        }
        if (clen != 1e9) {
            ans += clen;
            ans %= MOD;
        }
    }
}
*/

int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> K;
    int mxn = 0;
    FOR(it, K) {
        int n, m; cin >> n >> m;
        mxn = max(mxn, n);
        ni.push_back(n);
        Graph cur;
        cur.init(n);
        FOR(i, m) {
            int u, v; cin >> u >> v;
            u--, v--;
            cur.addEdge(u, v);
        }
        // cur.findWays();
        gs.push_back(cur);
        gs[it].bfs(0);
    }
    mxn *= 2;
    /*
    FOR(it, K) {
        FOR(j, ni[it]) {
            FOR(k, 2) {
            }
        }
        cout << '\n';
    }
    */
    // vector<int> val;
    // Solve(0, val);
    dp[0][0][0] = 1;
    FOR(pre, K) {
        FOR(modd, mxn + 1) {
            FOR(meven, mxn + 1) {
                FOR(take, ni[pre]) {
                    int nmodd = max(modd, gs[pre].dist[1][take]);
                    int nmeven = max(meven, gs[pre].dist[0][take]);
                    nmodd = min(nmodd, mxn);
                    nmeven = min(nmeven, mxn);
                    dp[pre + 1][nmodd][nmeven] += dp[pre][modd][meven];
                    /*
                    if (dp[pre][modd][meven] > 0) {
                    }
                    */
                }
            }
        }
    }
    // given k groups of pairs (ai, bi), find sum of min(max(a0 ... ak), max(b0 ... bk)) if you pick some pairs
    // so far we have, dp[first ki][max a][max b] = # ways
    // need dp[first ki]
    FOR(modd, mxn + 1) FOR(meven, mxn + 1) {
        ll clen = min(modd, meven);
        if (clen != mxn) {
            if (dp[K][modd][meven] != 0) {
                ans += (dp[K][modd][meven] * clen) % MOD;
                ans %= MOD;
            }
        }
    }
    cout << ans << '\n';
}

