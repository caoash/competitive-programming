#include <bits/stdc++.h> 
using namespace std;

typedef long long ll;

#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)

#define F first
#define S second

typedef pair<pair<int, int>, pair<int, int>> T;

int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};

double dp[105][105][205];
double cost[105][105];
int n, m, f, k;

void solve() {
    memset(cost, -1, sizeof(cost));
    memset(dp, 0, sizeof(dp));
    cin >> n >> m >> f >> k;
    f = min(f, 200);
    priority_queue<T, vector<T>, greater<T>> pq;
    pq.push({{0, f}, {0, 0}});
    FOR(i, n) FOR(j, m) FOR(l, f + 1) dp[i][j][l] = 1e9;
    dp[0][0][f] = 0;
    FOR(i, n) FOR(j, m) cost[i][j] = 1e9;
    FOR(i, k) {
        int a, b; double c;
        cin >> a >> b >> c;
        a--, b--;
        cost[a][b] = min(cost[a][b], c);
    }
    while (!pq.empty()) {
        T fr = pq.top();
        pq.pop();
        pair<int, int> pos = fr.S;
        if (fr.F.S) {
            FOR(c, 4) {
                int nx = pos.F + dx[c], ny = pos.S + dy[c]; 
                if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
                    int ng = fr.F.S - 1;
                    if (dp[nx][ny][ng] > dp[pos.F][pos.S][fr.F.S]) {
                        dp[nx][ny][ng] = dp[pos.F][pos.S][fr.F.S];
                        pq.push({{dp[nx][ny][ng], ng}, {nx, ny}});
                    } 
                }
            } 
        }
        if (cost[pos.F][pos.S] != -1 && fr.F.S < f) {
            int ng = fr.F.S + 1;
            if (dp[pos.F][pos.S][ng] > dp[pos.F][pos.S][fr.F.S] + cost[pos.F][pos.S]) {
                dp[pos.F][pos.S][ng] = dp[pos.F][pos.S][fr.F.S] + cost[pos.F][pos.S];
                pq.push({{dp[pos.F][pos.S][ng], ng}, {pos.F, pos.S}});
            }
        }
    }
    double ans = 1e9;
    FOR(g, f + 1) ans = min(ans, dp[n - 1][m - 1][g]);
    if (ans == 1e9) cout << "Stranded on the shoulder\n";
    else cout << fixed << setprecision(2) << ans << '\n';
}

int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t; cin >> t;
    while (t--) {
        solve();
    }
}

