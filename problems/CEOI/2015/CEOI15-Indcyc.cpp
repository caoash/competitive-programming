/*
 * If you can have length 3 cycles, you can find the earliest back edge in a DFS and it will be good.
 *
 * Transform into edge-graph, and now any length 3 cycles disappear, so you can just run this algo.
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

const int MX = 2000;
const int MOD = (int) (1e9 + 7);
const ll INF = (ll) 1e18;
 
int n, m;
 
int inc(int u, int v) {
    return MX * u + v;
}
 
bool neg[1000][1000];
vi fin[MX * MX];
bool vis[MX * MX];
bool done[MX * MX];
vector<pi> ed;
int anc[MX * MX];
bool found = false;
vi ret;
 
int cnt = 0;
 
void dfs(int v, int p) {
    if (found) return;
    vis[v] = true;
    vi togo;
    for (int to : fin[v]) {
        if (found) return;
        if (!done[to]) {
            if (!found && vis[to]) {
                found = true;
                int curr = v;
                while(curr != to) {
                    ret.pb((curr % 2000) + 1);
                    curr = anc[curr];
                }
                ret.pb((to % 2000) + 1);
                return;
            } else {
                togo.pb(to);
            }
        }
    }
    for (auto x : togo) {
        anc[x] = v;
        dfs(x, v);
    }
    done[v] = true;
}
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m; 
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--, v--;
        neg[u][v] = true;
        neg[v][u] = true;
        ed.pb(mp(u, v));
        ed.pb(mp(v, u));
    }
    for (int i = 0; i < sz(ed); i++) {
        int u = ed[i].f, v = ed[i].s;
        for (int j = 0; j < n; j++) {
            if (j != u && j != v && neg[v][j] && !neg[u][j]) {
                fin[inc(u, v)].pb(inc(v, j));
                fin[inc(v, u)].pb(inc(u, j));
            }
        }
    }
    for (auto &x : ed) {
        if (found) break;
        if (!done[inc(x.f, x.s)]) dfs(inc(x.f, x.s), -1);
    }
    if (!found) cout << "no" << '\n';
    else {
        for (int i = 0; i < sz(ret); i++) cout << ret[i] << " ";
        cout << '\n';
    }
}
