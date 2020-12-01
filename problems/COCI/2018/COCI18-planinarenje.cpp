/*
 * Consider the max matching of the graph. If every max matching doesn't contain a node, p, then the answer is Slavko because he
 * can always follow the max matching. Otherwise it's Mirko similarly.
 *
 * To recompute flow, you just remove the flow going through a node p and where it connects and compute augmenting paths again.
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
 
const int MX = 5005;
const int MOD = (int) (1e9 + 7);
const ll INF = (ll) 1e18;
 
int done[MX];
int pa[MX], pb[MX];
int opa[MX], opb[MX];
int it = 0;
vi adj[MX];
 
bool dfs(int v, int ig) {
    done[v] = it;
    for (int to : adj[v]) {
        if (pb[to] == -1) {
            pa[v] = to;
            pb[to] = v;
            return true;
        }
    }
    for (int to : adj[v]) {
        if (pb[to] == ig) continue;
        if (done[pb[to]] != it && dfs(pb[to], ig)) {
            pa[v] = to;
            pb[to] = v;
            return true;
        }
    }
    return false;
}
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m; cin >> n >> m;    
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--, v--;
        adj[u].pb(v);
    }
    memset(pa, -1, sizeof(pa));
    memset(pb, -1, sizeof(pb));
    auto aug = [&] (int ig) {
        int mm = 0;
        for (int i = 0; i < n; i++) {
            if (i == ig) continue;
            if (pa[i] == -1 && dfs(i, ig)) {
                ++mm;    
            }
        }
        return mm;
    };
    int best = 0;
    int add = 0;
    do {
        ++it;
        add = aug(-1);
        best += add;
    } while (add > 0);
    for (int i = 0; i < n; i++) {
        opa[i] = pa[i], opb[i] = pb[i];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) pa[j] = opa[j], pb[j] = opb[j];
        int old = pa[i];
        if (pa[i] == -1) {
            cout << "Mirko\n";
            continue;
        }
        int nbest = 0;
        bool change = (pb[old] == i);
        pa[i] = -1;
        if (change) pb[old] = -1;
        do {
            ++it;
            add = aug(i);
        } while (add > 0);
        for (int j = 0; j < n; j++) {
            if (j != i && pa[j] != -1) {
                nbest += (pb[pa[j]] == j);
            }
        }
        assert(nbest <= best);
        if (nbest == best) {
            cout << "Mirko\n";
        } else {
            cout << "Slavko\n";
        }
    }
}
