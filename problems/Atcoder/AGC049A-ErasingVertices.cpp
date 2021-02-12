#include <bits/stdc++.h> 
using namespace std;

using ll = long long;
using ld = long double;

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

const int MX = 105;
const int MOD = (int) (1e9 + 7);
const ll INF = (ll) 1e18;

bool vis[MX][MX];
int cnt[MX];

int main(){
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        for (int j = 0; j < n; j++) {
            vis[i][j] = (s[j] == '1');
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                vis[i][j] |= (vis[i][k] && vis[k][j]);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                vis[i][j] |= (vis[i][k] && vis[k][j]);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                vis[i][j] |= (vis[i][k] && vis[k][j]);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        vis[i][i] = 1;
        for (int j = 0; j < n; j++) {
            cnt[j] += vis[i][j];
        }
    }
    ld ans = 0;
    for (int i = 0; i < n; i++) {
        ans += (ld) ((ld) 1 / (ld) (cnt[i]));
    }
    cout << fixed << setprecision(9) << ans << '\n';
}

