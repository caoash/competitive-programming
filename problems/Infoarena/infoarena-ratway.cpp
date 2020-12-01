/*
Observe the final graph needs even number of edges and every edge needs even degree. Euler Tour seems useful here.

So, let's consider the Euler Tour of the graph. If you go into a node v in direction (u, v), you should exit it in direction (z, v) if
you go to node z. So take the Euler Tour and then alternate for a valid construction.
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

multiset<int> adj[200005];

vi tour;

void euler(int u) {
    while (sz(adj[u])) {
        auto it = adj[u].begin();
        int v = *it;
        adj[u].erase(it);
        adj[v].erase(adj[v].find(u));
        euler(v);
        tour.pb(u);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    ifstream cin("ratway.in");
    ofstream cout("ratway.out");
    int n, m; cin >> n >> m;
    vi odd;
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--, v--;
        adj[u].insert(v), adj[v].insert(u);
        // cout << "ed: " << u << " " << v << '\n';
    }
    for (int i = 0; i < n; i++) { 
        if (sz(adj[i]) % 2) {
            odd.pb(i);
        }
    }
    int ed = m;
    for (int i = 0; i < sz(odd); i += 2) {
        adj[odd[i]].insert(odd[i + 1]);
        adj[odd[i + 1]].insert(odd[i]);
        ++ed;
    }
    if (ed % 2 == 1) {
        adj[0].insert(0);
        adj[0].insert(0);
    }
    euler(0);
    reverse(all(tour));
    vector<pi> ans;
    for (int i = 0; i < sz(tour); i++) {
        int nxt = (i == sz(tour) - 1 ? 0 : i + 1);
        if(i % 2 == 0) ans.pb(mp(tour[i], tour[nxt]));
        else ans.pb(mp(tour[nxt], tour[i]));
    }
    cout << sz(ans) << '\n';
    for (pi x : ans) {
        cout << x.f + 1 << " " << x.s + 1 << '\n';
    }
}