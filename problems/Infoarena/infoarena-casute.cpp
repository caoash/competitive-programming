/*
 * Let bitset store the nodes some node can visit, then we can just find the first shared node that two nodes can visit in (N ^ 3) / 64.
 *
 * Requires some constant factor optimizations though:
 * - if i can reach j, then no need to do operations, just print i/j.
 * - use gp_hash_table and array sometimes instead of map to store things
 * - store visited array in a bitset too so you can do | operation 
 */

#pragma GCC optimize("unroll-loops")

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

const int MX = 3000;
const int MOD = (int) (1e9 + 7);
const ll INF = (ll) 1e18;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

#define hashbrown gp_hash_table

int heights[MX];
bitset<MX> reach[MX];
int n, m;
int rh[MX];
hashbrown<int, int> comp;
hashbrown<int, int> rev;
bitset<MX> vis;
vi adj[MX];

void dfs(int v) {
    vis[heights[v]] = 1;
    for (int to : adj[v]) {
        if (!vis[heights[to]]) {
            dfs(to);
        }
    }
}

int main(){
    ifstream cin("casute.in");
    ofstream cout("casute.out");
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    vector<int> vals;
    for (int i = 0; i < n; i++) {
        cin >> heights[i];
        vals.pb(heights[i]);
        rev[heights[i]] = i;
    }
    sort(all(vals));
    int cnt = 0;
    for (auto x : vals) {
        rh[cnt] = x;
        comp[x] = cnt++;
    }
    for (int i = 0; i < n; i++) heights[i] = comp[heights[i]];
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--, v--;
        adj[u].pb(v);
    }
    for (int i = 0; i < n; i++) {
        vis = 0;
        dfs(i);
        reach[i] |= vis;
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (i != j) {
                int ret = -1;
                if (reach[i][heights[j]]) ret = j;
                else if (reach[j][heights[i]]) ret = i;
                else {
                    bitset<MX> nval = reach[i] & reach[j];
                    int ch = nval._Find_first();
                    ret = rev[rh[ch]];
                    if (ch == MX) ret = -1;
                }
                ans = ans * (n + 1) + (ret + 1);
                ans %= 666013;
            }
        }
    }
    cout << ans << '\n';
}

