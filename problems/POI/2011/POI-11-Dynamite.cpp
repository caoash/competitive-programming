/*
 * Binary search for the answer. Then, you have to check minimum number of explosions you need to place to cover every marked node
 * if each node covers a distance of X.
 *
 * To do this, let dp1[v] = furthest uncovered marked node in the subtree of v.
 * Let dp2[v] = closest placed explosion to v.
 *
 * Then you can do like a greedy-ish dp, where you place an explosion every time the furthest away is x, and update.
 *
 * One detail you need to worry about is that an explosion can affect parents and nodes outside the subtree that aren't
 * parents. To deal with this, we can say that some marked node isn't marked if the closest placed explosion <= x. Also, when transitioning
 * from children, if that childs furthest node is covered by the current nodes closest explosion then we don't transition, since that child
 * no longer becomes marked.
 */

#include <bits/stdc++.h> 
using namespace std;

using ll = long long;

using vi = vector<int>;
using vl = vector<ll>;
#define pb push_back
#define rsz resize
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using pi = pair<int,int>;
#define f first
#define s second
#define mp make_pair

const int MX = 300005;
const int MOD = (int) (1e9 + 7);
const ll INF = (ll) 1e18;

int n, m;
int d[MX];
vector<int> adj[MX];
int dp1[MX], dp2[MX];
int need = 0;

void dfs(int v, int p, int mid) {
    dp1[v] = -1;
    dp2[v] = 987654321;
    for (int to : adj[v]) {
        if (to != p) {
            dfs(to, v, mid);
            dp2[v] = min(dp2[v], dp2[to] + 1);
        }
    }
    for (int to : adj[v]) {
        if (to != p) {
            if (dp1[to] + 1 + dp2[v] <= mid) {
                continue;
            }
            if (dp1[to] != -1) {
                dp1[v] = max(dp1[v], dp1[to] + 1);
            }
        }
    }
    if (dp1[v] == -1 && d[v] && dp2[v] > mid) {
        dp1[v] = 0;
    }
    if (dp1[v] == mid || (v == 0 && dp1[v] != -1)) {
        dp2[v] = 0;
        dp1[v] = -1;
        ++need;
    }
    return;
}

bool solve(int mid) {
    dfs(0, -1, mid);    
    if (need > m) {
        return false;
    }
    return true;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        cin >> d[i];
        cnt += d[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        u--, v--;
        adj[u].pb(v), adj[v].pb(u);
    }
    int lo = 1, hi = n;
    int ans = 0;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        need = 0;
        if (solve(mid)) {
            hi = mid - 1;
            ans = mid;
        }
        else {
            lo = mid + 1;
        }
    }
    if (m >= cnt) {
        cout << 0 << '\n';
    }
    else {
        cout << ans << '\n';
    }
}

