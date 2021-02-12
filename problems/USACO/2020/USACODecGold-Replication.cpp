#include <bits/stdc++.h> 
using namespace std;

using ll = long long;

using vi = vector<int>;
using vl = vector<ll>;
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define lb lower_bound
#define ub upper_bound

using pi = pair<int,int>;
#define f first
#define s second
#define mp make_pair

const int MX = 1005;
const int MOD = (int) (1e9 + 7);
const ll INF = (ll) 1e18;

int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};

int n, d;
char grid[MX][MX];
int wall[MX][MX], beg[MX][MX], cent[MX][MX];
bool vis[MX][MX];


void go(vector<pair<pi, int>> &sts, int dist[MX][MX], bool chk) {
    memset(vis, false, sizeof(vis));
    for (int i = 0; i < MX; i++) {
        for (int j = 0; j < MX; j++) {
            dist[i][j] = 1e9;
        }
    }
    queue<pi> bfs;
    for (auto x : sts) {
        bfs.push(x.f);
        dist[x.f.f][x.f.s] = x.s;
    }
    while (!bfs.empty()) {
        pi curr = bfs.front();
        bfs.pop();
        if (vis[curr.f][curr.s]) continue;
        if (chk) {
            if (wall[curr.f][curr.s] < (dist[curr.f][curr.s] / d) + 1) {
                continue;
            }
        }
        for (int k = 0; k < 4; k++) {
            int nx = curr.f + dx[k], ny = curr.s + dy[k];
            if (!vis[nx][ny] && nx >= 0 && nx < n && ny >= 0 && ny < n && grid[nx][ny] != '#') {
                if (dist[nx][ny] > dist[curr.f][curr.s] + 2) {
                    dist[nx][ny] = dist[curr.f][curr.s] + 1;
                    bfs.push(mp(nx, ny));
                }
            }
        }
        vis[curr.f][curr.s] = true;
    }
}

int main(){
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> d;
    vector<pair<pi, int>> bord, sts;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == '#') bord.pb(mp(mp(i, j), 0));
            else if (grid[i][j] == 'S') sts.pb(mp(mp(i, j), 0));
        }
    }
    go(bord, wall, false);
    go(sts, beg, true);
    vector<pair<pi, int>> cents;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (beg[i][j] != 1e9) {
                cent[i][j] = wall[i][j] - 1;
            } else {
                cent[i][j] = -1e9;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cent[i][j + 1] = max(cent[i][j + 1], cent[i][j] - 1);
        }
        for (int j = n - 1; j >= 0; j--) {
            cent[i][j] = max(cent[i][j], cent[i][j + 1] - 1);
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1; j++) {
            cent[j + 1][i] = max(cent[j + 1][i], cent[j][i] - 1);
        }
        for (int j = n - 1; j >= 0; j--) {
            cent[j][i] = max(cent[j][i], cent[j + 1][i] - 1);
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) ans += (cent[i][j] >= 0);
    cout << ans << '\n';
}


