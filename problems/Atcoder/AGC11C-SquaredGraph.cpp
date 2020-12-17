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

const int MX = 200005;
const int MOD = (int) (1e9 + 7);
const ll INF = (ll) 1e18;

vi adj[MX];

ll ccs = 0, bccs = 0, dcc = 0;
bool bi = true;
int col[MX];
int deg[MX];

int main(){
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll n, m; cin >> n >> m;
    memset(col, -1, sizeof(col));
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--, v--;
        adj[u].pb(v), adj[v].pb(u);
        deg[u]++, deg[v]++;
    }
    for (int i = 0; i < n; i++) {
        if (col[i] == -1) {
            ++ccs;
            queue<int> q;
            col[i] = 0;
            q.push(i);
            bi = true;
            while (!q.empty()) {
                int curr = q.front();
                q.pop();
                for (int to : adj[curr]) {
                    if (col[to] == -1) {
                        col[to] = col[curr] ^ 1;
                        q.push(to);
                    } else {
                        bi &= (col[curr] != col[to]);           
                    }
                }
            }
            if (deg[i] == 0) ++dcc;
            else if (bi) ++bccs;
        }
    }
    ll ans = ((ccs - dcc) * (ccs - dcc)) + (bccs * bccs) + ((dcc * n * 2) - (dcc * dcc));
    cout << ans << '\n';
}

