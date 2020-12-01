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

int ex[MX][MX][8];
ll prod[MX][MX][8];
ll grid[MX][MX];
int dx = {0, 1, 0, -1, 1, 1, -1, -1};
int dy = {1, 0, -1, 0, -1, 1, -1, 1};

int main(){
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }
    auto ok = [&] (int x, int y) {
        return x >= 0 && y >= 0 && x < n && y < n;
    };
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < 8; k++) {
                prod[i][j][k] = grid[i][j];
                ex[i][j][k] = 1;
                int nx = i + dx[k], ny = j + dy[k];
                if (ok(nx, ny)) {
                    if (grid[nx][ny] != 0) {
                        prod[i][j][k] *= prod[nx][ny][k];
                        prod[i][j][k] %= MOD;
                        ex[i][j][k] = ex[nx][ny][k] + 1;
                    }
                }
            }
        }
    }
}

