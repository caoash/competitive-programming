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

/*
Take xor distance from root. Any two xor with the same value have a xor of 0 because the lca to root cancels.

So, use DSU to add in reverse to simulate removing. Then, x of some value contributes x * (x - 1) / 2. Update counts
by merging sets in the DSU, but do it small to large so it passes in time.
*/

const int MX = 100005;

vector<pi> adj[MX]; int dist[MX]; ll ans = 0;

ll sq(ll x) {
    return (x * (x - 1)) / 2;
}

template<int SZ> struct DSU{
    int p[SZ], sz[SZ]; map<int, int> vals[SZ];
    void init(){
        for(int i = 0; i < SZ; i++){
            p[i] = i; sz[i] = 1;
            vals[i][dist[i]] = 1;
        }
    }
    int find(int x){
        return p[x] = (p[x] == x ? x : find(p[x]));
    }
    void merge(int u, int v){
        int a = find(u); int b = find(v);
        if(a != b){
            if(sz[a] < sz[b]){
                swap(a,b);
            }
            p[b] = a;
            sz[a] += sz[b];
            // if (sz(vals[a]) < sz(vals[b])) {
                // swap(vals[a], vals[b]);
            // }
            for (pi x : vals[b]) {
                ans -= sq(vals[a][x.f]);
                ans -= sq(x.s);
                vals[a][x.f] += x.s;
                ans += sq(vals[a][x.f]);
            }
            vals[b].clear();
        }
    }
};

void dfs(int v, int p){
    for (pi to : adj[v]) {
        if (to.f != p) {
            dist[to.f] = dist[v] ^ to.s;
            dfs(to.f, v);
        }
    }
}

DSU<MX> dsu; vector<pi> ed;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v, w; cin >> u >> v >> w;
        u--, v--;
        adj[u].pb(mp(v, w)), adj[v].pb(mp(u, w));
        ed.pb(mp(u, v));
    }
    vector<pi> order;
    for (int i = 0; i < n - 1; i++) {
        int x; cin >> x;
        x--;
        order.pb(ed[x]);
    }
    dfs(0, -1);
    dsu.init(); 
    reverse(all(order));
    vector<ll> ret;
    for (pi x : order) {
        ret.pb(ans);
        dsu.merge(x.f, x.s);
    }
    ret.pb(ans);
    reverse(all(ret));
    for (ll x : ret) {
        cout << x << '\n';
    }
}