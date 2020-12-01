/*
 * Let du[] = shortest path from u and dv[] = shortest path from v.
 * Observe that in the shortest path DAG of s -> t, you want to pick some path with endpoints i, j that minimizes du[i] + dv[j].
 * You can do DP on dag by fixing i, then the answer is du[i] + min(dv[j]) such that j is on the shortest path from s -> t and i can reach j.
 * Since it's a DAG, we can just do dp1[i] = minimum dv[j] for j that can reach i, and dp2[i] = min dv[j] for j that i can reach.
 *
 * You can compute this by doing DP on the dag and then reversing the graph and doing DP again. Note that I don't compute the DAG or reverse it directly,
 * I just flip the condition needed to form a shortest path DAG (shortest path from s -> edge.f + edge.s = shortest path from s -> edge.f if edge stores endpoint, weight)
 */

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

using T = pair<ll, int>;

int n;
int a, b, c, d;
ll ds[MX], dt[MX], du[MX], dv[MX];
ll dp[MX][2];
vector<T> adj[MX];

void dijkstra(int s, ll dist[MX]) {
    vector<bool> vis(n);
    priority_queue<T, vector<T>, greater<T>> pq;  
    for (int i = 0; i < n; i++) dist[i] = INF;
    dist[s] = 0;
    pq.push(mp(dist[s], s));
    while (!pq.empty()) {
        T curr = pq.top();
        pq.pop();
        for (auto to : adj[curr.s]) {
            int v = to.s;
            if (!vis[v]) {
                if (dist[v] > dist[curr.s] + to.f) {
                    dist[v] = dist[curr.s] + to.f;
                    pq.push(mp(dist[v], v));
                }
            }
        }
        vis[curr.s] = true;
    }
}

ll go(int v, int ok) {
    if (ds[v] + dt[v] != dt[a]) return INF;
    if (dp[v][ok] != INF) return dp[v][ok];
    dp[v][ok] = dv[v];
    for (auto to : adj[v]) {
        // directed ff -> fs
        int ff = to.s, fs = v;
        if (ok) swap(ff, fs);
        if (ds[ff] + to.f != ds[fs]) continue;
        assert(ds[ff] + to.f <= ds[fs]);
        dp[v][ok] = min(dp[v][ok], go(to.s, ok));
    }
    return dp[v][ok];
}

int main(){
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int m;
    cin >> n >> m;
    cin >> a >> b;
    cin >> c >> d;
    a--, b--, c--, d--;
    for (int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w;
        u--, v--;
        adj[u].pb(mp(w, v)), adj[v].pb(mp(w, u));
    }
    for (int i = 0; i < n; i++) dp[i][0] = INF, dp[i][1] = INF;
    dijkstra(a, ds);
    dijkstra(b, dt);
    dijkstra(c, du);
    dijkstra(d, dv);
    go(b, 0);
    go(a, 1);
    ll ans = dv[c];
    for (int i = 0; i < n; i++) {
        ans = min(ans, du[i] + min(dp[i][0], dp[i][1]));
    }
    cout << ans << '\n';
}

