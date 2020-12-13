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
int dist[MX];
bool vis[MX];
 
void bfs(int s1, int s2) {
    memset(dist, 0x3f3f3f, sizeof(dist));
    memset(vis, false, sizeof(vis));
    queue<int> q; 
    q.push(s1), dist[s1] = 0;
    if (s2 != -1) {
        q.push(s2), dist[s2] = 0;
    }
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        for (int to : adj[curr]) {
            if (!vis[to] && dist[to] > dist[curr] + 1) {
                dist[to] = dist[curr] + 1; 
                q.push(to);
            }
        }
        vis[curr] = true;
    }
}
 
int main(){
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, k; cin >> n >> k;
    vector<pi> eds;
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        u--, v--;
        adj[u].pb(v), adj[v].pb(u);
        eds.pb(mp(u, v));
    }
    int best = 1e9;
    if (k % 2) {
        int lim = (k - 1) / 2; 
        for (auto e : eds) {
            bfs(e.f, e.s); 
            int ans = 0;
            for (int i = 0; i < n; i++) {
                if (dist[i] > lim) ++ans;
            }
            best = min(best, ans);
        }
    } else {
        int lim = k / 2;
        for (int i = 0; i < n; i++) {
            bfs(i, -1);
            int ans = 0;
            for (int j = 0; j < n; j++) {
                if (dist[j] > lim) ++ans;
            }
            best = min(best, ans);
        }
    }
    cout << best << '\n';
}
 
