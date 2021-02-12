#include <bits/stdc++.h> 
using namespace std;

typedef long long ll;

#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)

#define F first
#define S second

int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};

bool adj[1005][1005][4];
int deg[1005][1005], psum[1005][1005];
char c[1005][1005];
bool vis[1005][1005];

void dfs(int x, int y, int x1, int y1, int x2, int y2) {
    vis[x][y] = true;
    FOR(k, 4) {
        if (!adj[x][y][k]) continue;
        int nx = x + dx[k], ny = y + dy[k];
        if (!vis[nx][ny] && nx >= x1 && nx <= x2 && ny >= y1 && ny <= y2) {
            dfs(nx, ny, x1, y1, x2, y2);
        }
    }
}

int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m, q; cin >> n >> m >> q;
    FOR(i, n) {
        string s; cin >> s;
        FOR(j, m) {
            c[i][j] = s[j];
        }
    }
    FOR(i, n) FOR(j, m) {
        FOR(k, 4) {
            int ni = i + dx[k], nj = j + dy[k];
            if (ni < n && nj < m && ni >= 0 && nj >= 0) {
                if (c[i][j] == c[ni][nj]) {
                    adj[i][j][k] = true;
                    deg[i][j]++;
                }
            }
        }
    }
    FOR(i, n) FOR(j, m) {
        psum[i][j] = deg[i][j];
        if (i) psum[i][j] += psum[i - 1][j];
        if (j) psum[i][j] += psum[i][j - 1];
    }
    auto qry = [&] (int x1, int y1, int x2, int y2) {
        int ans = psum[x2][y2];
        if (x1 > 0) ans -= psum[x1 - 1][y2];
        if (y1 > 0) ans -= psum[x2][y1 - 1];
        if (x1 > 0 && y1 > 0) ans += psum[x1 - 1][y1 - 1];
        return ans;
    };
    FOR(i, q) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        x1--, y1--, x2--, y2--;
        // if (n <= 50 && m <= 50) {
        /*
            FOR(j, n) FOR(k, m) vis[j][k] = false;
            int cc = 0;
            F0R(j, x1, x2 + 1) F0R(k, y1, y2 + 1) {
                if (!vis[j][k]) {
                    ++cc;
                    dfs(j, k, x1, y1, x2, y2);
                }
            }
            cout << cc << '\n';
            */
        // } else {
            ll cans = qry(x1, y1, x2, y2);
            cout << cans << '\n';
            cans /= 2;
            int a = (x2 - x1 + 1), b = (y2 - y1 + 1);
            cout << (a * b) - cans << '\n';
        // }
    }
}

