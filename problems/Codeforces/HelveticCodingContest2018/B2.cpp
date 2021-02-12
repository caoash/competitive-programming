#include <bits/stdc++.h> 
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pi;

#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)

#define F first
#define S second

const int MX = 100005;

int n;
vector<int> adj[MX];
pi dep[MX];
bool marked[MX];
ll ans[MX], anc[MX];
pi best = {-1, -1};
multiset<pi> pq;
ll ret = 1;

void dfs_init(int v, int p, ll d) {
    if (d > best.S) best = {v, d};
    for (int to : adj[v]) {
        if (to != p) {
            dfs_init(to, v, d + 1);
        }
    }
}

void dfs_dep(int v, int p) {
    dep[v] = {v, 0};
    for (int to : adj[v]) {
        if (to != p) {
            anc[to] = v;
            dfs_dep(to, v);
            if (dep[to].S + 1 > dep[v].S) dep[v] = {dep[to].F, dep[to].S + 1};
        }
    }
}

void push(int v) {
    for (int to : adj[v]) {
        if (to != anc[v] && !marked[to]) {
            dbg("INSERTING", dep[to].S, dep[to].F);
            pq.insert({dep[to].S, dep[to].F});
        }
    }
}

void tri(int it) {
    if (!pq.empty()) {
        auto curr = (--pq.end());
        int end = curr->S;
        dbg(curr->F, curr->S);
        pq.erase(curr);
        while (!marked[end]) {
            marked[end] = true;
            ++ret;
            push(end);
            end = anc[end];
        }
    }
    ans[it] = ret;
}

int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    FOR(i, n - 1) {
        int u, v; cin >> u >> v;
        u--, v--;
        adj[u].push_back(v), adj[v].push_back(u);
    }
    dfs_init(0, -1, 0);
    dfs_dep(best.F, -1);
    ans[0] = ret;
    marked[best.F] = true;
    push(best.F);
    // dbg(best.F);
    F0R(i, 1, n) {
        tri(i);
    }
    FOR(i, n) cout << ans[i] << " ";
    cout << '\n';
}

