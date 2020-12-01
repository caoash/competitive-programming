/*
First, observe that bridges are the only edges that need to be directed. Any other edge will still make a CC connected
even after removing, so it doesn't matter how you direct it. Then, store how many "start" and "end" points there are in the
bridge tree, and if there are more start points you direct one way and the other with more end points. This works since the paths
aren't contridictory.

Be careful with multiple edges and remember that the graph isn't connected.
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

const int MX = 200005;

bool vis[MX]; vi adj[MX]; int tout[MX], tin[MX], dep[MX], par[MX]; set<pi> brid; vi tr[MX]; int cols[MX];

map<pi, int> edc;

int cnt = 0;

void dfs(int v, int p){
    vis[v] = true;
    tin[v] = tout[v] = cnt++;
    for (int to : adj[v]) {
        if(to != p){
            if(vis[to]){
                tout[v] = min(tout[v], tin[to]);
            }
            else{
                par[to] = v;
                dfs(to, v);
                tout[v] = min(tout[v], tout[to]);
                if(tout[to] > tin[v]){
                    brid.insert(mp(v, to));
                    brid.insert(mp(to, v));
                }
            }
        }
    }
}

void dfs2(int v, int p) {
    vis[v] = true;
    for (int to : tr[v]) {
        dep[to] = dep[v] + 1;
        dfs2(to, v);
        cols[v] += cols[to];
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m; cin >> n >> m;
    memset(tout, -1, sizeof(tout));
    memset(tin, -1, sizeof(tin));
    vector<pi> eds;
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--, v--;
        adj[u].pb(v), adj[v].pb(u);
        eds.pb(mp(u, v));
        edc[mp(u, v)]++, edc[mp(v, u)]++;
    }
    int p; cin >> p;
    for (int i = 0; i < p; i++) {
        int x, y; cin >> x >> y;
        x--, y--;
        cols[x]++, cols[y]--;
    }
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            dfs(i, -1);
        }
    }
    for (int i = 0; i < n; i++) {
        if (i != 0) {
            tr[par[i]].pb(i);
        }
    }
    memset(vis, false, sizeof(vis));
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            dfs2(i, -1);
        }
    }
    for (int i = 0; i < m; i++) {
        pi curr = eds[i];
        if (brid.count(mp(curr.f, curr.s)) && edc[mp(curr.f, curr.s)] == 1) {
            if (dep[curr.f] == dep[curr.s]) {
                cout << "B";
            }
            else if (dep[curr.f] > dep[curr.s]) {
                if (cols[curr.f] > 0) {
                    cout << "R";
                }
                else if (cols[curr.f] < 0) {
                    cout << "L";
                }
                else {
                    cout << "B";
                }
            }
            else {
                if (cols[curr.s] > 0) {
                    cout << "L";
                }
                else if(cols[curr.s] < 0) {
                    cout << "R";
                }
                else {
                    cout << "B";
                }
            }
            
        }
        else {
            cout << "B";
        }
    }
}