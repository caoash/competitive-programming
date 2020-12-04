/*
 *
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

bool st[MX];
int en[MX];
bool done[MX];
int deg[MX];
vi adj[MX], rem[MX];

int main(){
    ifstream cin("gathering.in");
    ofstream cout("gathering.out");
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m; cin >> n >> m;
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        u--, v--;
        deg[u]++, deg[v]++;
        adj[u].pb(v), adj[v].pb(u);
    }
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        a--, b--;
        st[a] = true, en[b]++;
        rem[a].pb(b);
    }
    queue<int> to_rem;
    for (int i = 0; i < n; i++) {
        if (deg[i] == 1 && !en[i]) to_rem.push(i);
    }
    int del = 0;
    while (!to_rem.empty()) {
        int fr = to_rem.front();
        if (del == n - 1) break;
        to_rem.pop();
        for (int to : adj[fr]) {
            if (done[to]) continue;
            deg[to]--;
            if (deg[to] == 1 && en[to] == 0) to_rem.push(to);
        }
        for (int to : rem[fr]) {
            if (done[to]) continue;
            en[to]--;
            if (deg[to] == 1 && en[to] == 0) to_rem.push(to);
        }
        done[fr] = true;
        ++del;
    }
    int not_rem = 0;
    for (int i = 0; i < n; i++) {
        // dbg(i, done[i]);
        if (!done[i]) ++not_rem; 
    }
    if (not_rem > 1) {
        for (int i = 0; i < n; i++) cout << 0 << '\n';
    } else {
        assert(!to_rem.empty());
        int bad = to_rem.front();
        assert(!st[bad]);
        queue<int> bfs;
        memset(done, false, sizeof(done));
        bfs.push(bad);
        while (!bfs.empty()) {
            int cur = bfs.front();
            bfs.pop();
            for (int to : adj[cur]) {
                if (!done[to] && !st[to]) bfs.push(to);
            }
            done[cur] = true;
        }
        for (int i = 0; i < n; i++) {
            if (done[i]) cout << 1 << '\n';
            else cout << 0 << '\n';
        }
    }
}

