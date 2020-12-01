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
using pl = pair<ll, ll>;
#define f first
#define s second
#define mp make_pair

const int MX = 200005;
const int MOD = (int) (1e9 + 7);
const ll INF = (ll) 1e18;

int n;
vi adj[MX];
ll dp[MX][2];
int fr[MX];
int ret[MX];

void dfs(int v, int p) {
    pl dp_curr = mp(0, INF); 
    pl dp_prev = mp(INF, INF);
    for (int to : adj[v]) {
        if (to != p) {
            dfs(to, v);
            swap(dp_curr, dp_prev);
            vl trans = {
                dp_prev.f + dp[to][1] + 2,
                dp_prev.s + dp[to][1],
                dp_prev.s + dp[to][0] + 2,
                dp_prev.f + dp[to][0] + 2,
            };
            pair<ll, int> best = mp(min(INF, trans[0]), 0);
            for (int i = 1; i < 4; i++) {
                best = min(best, mp(min(INF, trans[i]), i));
            }
            dp_curr.s = best.f;
            fr[to] = best.s;
            dp_curr.f = min(INF, dp_prev.f + dp[to][1]);
        }
    }
    dp[v][0] = dp_curr.f;
    dp[v][1] = dp_curr.s;
}

void construct(int v, int p, int x);

void go(int v, vi &tos, int pre, bool done) {
    if (pre < 0) return;
    int to = tos[pre];
    if (done) {
        go(v, tos, pre - 1, true);
        construct(to, v, 1);
    } else {
        int need = fr[to];
        if (need == 1 || need == 2) {
            go(v, tos, pre - 1, false);
            if (need == 1) {
                construct(to, v, 1);
            } else {
                construct(to, v, 0);
                ret[to] = ret[v];
                ret[v] = to;
            }
        } else {
            go(v, tos, pre - 1, true);
            if (need == 0) {
                construct(to, v, 1);
                ret[v] = ret[to];
                ret[to] = v;
            } else {
                construct(to, v, 0);
                ret[v] = to;
                ret[to] = v;
            }
        }
    }
}

void construct(int v, int p, int x) {
    if (x == 0) {
        for (int to : adj[v]) {
            if (to != p) {
                construct(to, v, 1);
            }
        }
    } else {
        vi gos;
        for (int to : adj[v]) if (to != p) gos.pb(to);
        go(v, gos, sz(gos) - 1, false);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        u--, v--;
        adj[u].pb(v), adj[v].pb(u);
    }
    dfs(0, -1);
    cout << dp[0][1] << '\n';
    memset(ret, -1, sizeof(ret));
    construct(0, -1, 1);
    for (int i = 0; i < n; i++) {
        cout << ret[i] + 1 << " ";
    }
    cout << '\n';
}

