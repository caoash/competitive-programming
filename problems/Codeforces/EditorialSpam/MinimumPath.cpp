#include <bits/stdc++.h> 
using namespace std;
 
typedef long long ll;
typedef pair<int, pair<bool, bool>> T;
 
#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)
 
#define F first
#define S second
 
const int MX = 200005;

struct T_Hash {
    size_t operator() (const T& val) const {
        return val.F ^ val.S.F ^ val.S.S;
    }
};
 
priority_queue<pair<ll, T>, vector<pair<ll, T>>, greater<pair<ll, T>>> pq;
vector<pair<int, int>> adj[MX];
unordered_set<T, T_Hash> vis;
unordered_map<T, ll, T_Hash> dist;
 
int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m; cin >> n >> m;
    FOR(i, m) {
        int u, v, w; cin >> u >> v >> w;
        u--, v--;
        adj[u].push_back({v, w});        
        adj[v].push_back({u, w});
    }
    pq.push({0, {0, {false, false}}});
    auto prop = [&] (T curr, T trans, int ed) {
        if (!vis.count(trans)) {
            if (dist.find(trans) == dist.end()) {
                dist[trans] = dist[curr] + ed;
                pq.push({dist[trans], trans});
            } else {
                if (dist[curr] + ed < dist[trans]) {
                    dist[trans] = dist[curr] + ed;
                    pq.push({dist[trans], trans});
                }
            }
        }
    };
    while (!pq.empty()) {
        auto curr = pq.top();
        pq.pop();
        int v = curr.S.F;
        if (!vis.count(curr.S)) {
            for (auto to : adj[v]) {
                pair<bool, bool> use = curr.S.S;
                T trans = {to.F, {use.F, use.S}};
                prop(curr.S, trans, to.S);
                if (!use.F) {
                    trans = {to.F, {true, use.S}};
                    prop(curr.S, trans, 0);
                }
                if (!use.S) {
                    trans = {to.F, {use.F, true}};
                    prop(curr.S, trans, 2 * to.S);
                }
                if (!use.F && !use.S) {
                    trans = {to.F, {true, true}};
                    prop(curr.S, trans, to.S);
                }
            }
            vis.insert(curr.S);
        }
    }
    F0R(i, 1, n) {
        T cur = {i, {true, true}};
        cout << dist[cur] << " ";
    }
    cout << '\n';
}
