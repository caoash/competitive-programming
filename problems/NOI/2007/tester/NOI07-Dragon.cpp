#include <bits/stdc++.h> 
using namespace std;

typedef long long ll;

#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)

#define F first
#define S second

const int MX = 3005;
const ll INF = (ll) (1e18);

vector<ll> dp[MX][2];
vector<pair<int, int>> adj[MX];
ll num[MX];

int n, m, k;

vector<ll> Comb(int v, int to, int c2) {
    vector<ll> &a = dp[v][c2];
    vector<ll> c(a.size() + max(dp[to][0].size(), dp[to][1].size()) - 1, INF);
    FOR(c1, 2) {
        vector<ll> &b = dp[to][c1];
        FOR(i, a.size()) FOR(j, b.size()) {
            if (a[i] != INF && b[j] != INF) {
                int ad = (c2 == c1 ? num[to] : 0);
                if (m > 2 && c2 == c1 && c2 == 1) ad = 0;
                c[i + j] = min(c[i + j], a[i] + b[j] + ad);
            }
        }
    }
    return c;
}

void dfs_init(int v, int p) {
    for (auto to : adj[v]) {
        if (to.F != p) {
            num[to.F] = to.S;
            dfs_init(to.F, v);
        }
    }
}

void dfs_dp(int v, int p) {
    dp[v][0] = {0};
    dp[v][1] = {0};
    for (auto to : adj[v]) {
        if (to.F != p) {
            dfs_dp(to.F, v);
            FOR(i, 2) {
                dp[v][i] = Comb(v, to.F, i);
            }
        }
    }
    dp[v][0].insert(dp[v][0].begin(), INF);
}

void SolveSmall() {
    { // clear stuff
        FOR(i, n) {
            adj[i].clear();
            dp[i][0].clear(), dp[i][1].clear();
            num[i] = 0;
        }
    }
    FOR(i, n - 1) {
        int u, v, w; cin >> u >> v >> w;
        u--, v--;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    dfs_init(0, -1);
    dfs_dp(0, -1);
    if (k >= dp[0][0].size() || (m > (n - k))) cout << -1 << '\n';
    else {
        cout << (dp[0][0][k] == INF ? -1 : dp[0][0][k]) << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T = 1;
    while (T--) {
        cin >> n >> m >> k;
        SolveSmall();
    }
}

