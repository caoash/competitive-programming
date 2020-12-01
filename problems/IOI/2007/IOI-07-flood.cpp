/*
Same as editorial. Simulate walking on the outside border of the grid by taking the outermost edge (right, forward, left, back) with
a DFS. Keep doing this until you hit a loop and unmark everything not on the loop. Anything not marked will be destroyed. 
*/

#include <bits/stdc++.h> 
using namespace std;

using ll = long long;

using vi = vector<int>;
#define pb push_back
#define rsz resize
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using pi = pair<int,int>;
#define f first
#define s second
#define mp make_pair

vector<pair<pi, int>> pt; vector<pi> adj[100005][4];

const int go[] = {1, 0, 3, 2};

int gdir (pi a, pi b) {
    if (a.f == b.f) {
        return (b.s > a.s ? 0 : 2);
    }
    else {
        return (b.f > a.f ? 1 : 3);
    }
}

bool vis[100005]; vi fans;

int dfs(int v, int d) {
    if (vis[v]) return v;
    vis[v] = true;
    for (int i = 0; i < 4; i++) {
        int nxt = (d + go[i]) % 4;
        if (adj[v][nxt].empty()) {
            continue;
        }
        pi to = adj[v][nxt].front();
        adj[v][nxt].clear();
        adj[to.f][(nxt + 2) % 4].clear(); 
        int ret = dfs(to.f, nxt);
        if (ret == -1) {
            fans.pb(to.s);
            continue;
        }
        if (ret != v) {
            vis[v] = false;
            return ret;
        }
    } 
    vis[v] = false;
    return -1;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        pi curr;
        cin >> curr.f >> curr.s;
        pt.pb(mp(curr, i));
    }
    int w; cin >> w;
    for (int i = 0; i < w; i++) {
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a][gdir(pt[a].f, pt[b].f)].pb(mp(b, i));
        adj[b][gdir(pt[b].f, pt[a].f)].pb(mp(a, i));
    }
    sort(all(pt));
    for (pair<pi, int> x : pt) {
        dfs(x.s, 0);
    }
    cout << sz(fans) << '\n';
    for (int x : fans) {
        cout << x + 1 << '\n';
    }
}