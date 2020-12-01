/*
 * Problem forms a functional graph.
 *
 * To achieve maximum, notice that you can't kill any leaves. However, you can kill the rest of the nodes, unless the connected component is only a cycle (then you have to leave one alive).
 *
 * To achieve minimum, notice that leaves must kill their parents. Then their parents won't kill, but the parents of their parents will.
 *
 * You can simulate using a BFS.
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

const int MX = 1000005;
const int MOD = (int) (1e9 + 7);
const ll INF = (ll) 1e18;

int n;
int p[MX], deg[MX], dead[MX];
bool vis[MX];
int ans;
bool found = false;

void dfs_cyc(int v) {
    vis[v] = true, ++ans;
    int to = p[v];
    if (!vis[to]) dfs_cyc(to);
}

int main(){
    freopen("paintball.in", "r", stdin);
    freopen("paintball.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> p[i]; 
        p[i]--;
        deg[p[i]]++;
    }
    int amx = 0, amn = 0;
    for (int i = 0; i < n; i++) {
        ans = 0;
        if (!vis[i] && deg[i] == 0) {
            dfs_cyc(i);
            amx += (ans - 1);
        }
    }
    for (int i = 0; i < n; i++) {
        ans = 0;
        if (!vis[i]) {
            dfs_cyc(i);
            amx += (ans - 1) + (ans == 1); 
        }
    }
    memset(dead, -1, sizeof(dead));
    memset(vis, false, sizeof(vis));
    queue<int> bfs;
    for (int i = 0; i < n; i++) {
        if (deg[i] == 0) {
            dead[i] = 0;
            bfs.push(i);
        }
    }
    while (!bfs.empty()) {
        int curr = bfs.front();
        bfs.pop();
        vis[curr] = true;
        int to = p[curr];
        if (!vis[to]) {
            ++amn;
            vis[to] = true;
            if (!vis[p[to]] && --deg[p[to]] == 0) {
                bfs.push(p[to]);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (dead[i] == 1) ++amn;
        ans = 0;
        if (!vis[i]) {
            dfs_cyc(i);
            amn += ans - (ans / 2);
        }
    }
    assert(amn <= amx);
    cout << amn << " " << amx << '\n';
}

