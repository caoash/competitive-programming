/*
Very elegant construction problem. So first we do standard SCC compression into DAG, and we assume
you can get every single node in an SCC. We can prove this guess by construction.

Building the permutation 1 by 1, do something similar to CCO 2020 p1, where you add values in between
valid values. Then, to shift the permutation, keep performing the same operation in the first value until
you've hit every first value which is possible since it's a SCC.
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

const int maxn = 2005;

int n; vi scc_val[maxn]; set<int> scc_adj[maxn]; bool used[maxn]; vi order; 
int scc_num[maxn], scc_sz[maxn], ans[maxn], pre[maxn]; vector<pi> ed; bool can[maxn][maxn];
vi rets[maxn];

vi solve(vi &nodes) {
    int m = sz(nodes);
    vi nxt(m);
    nxt.assign(m, -1);
    stack<pi> todo; 
    set<pi> has;
    set<int> path;
    auto add = [&] (const int &v) {
        path.insert(v);
        for (int i = 0; i < m; i++) {
            if (i == v) continue;
            if (!has.count(mp(i, v)) && !path.count(i) && can[nodes[v]][nodes[i]]) {
                has.insert(mp(i, v));
                todo.push(mp(i, v));
            }
        }
    };
    add(0);
    while(!todo.empty()){
        pi curr = todo.top(); todo.pop();
        if(path.count(curr.f)) {
            continue;
        }
        if(!path.count(curr.f)) {
            nxt[curr.f] = nxt[curr.s];
            nxt[curr.s] = curr.f;
            add(curr.f); 
        }
    }
    int st = 0;
    vi ret;
    ret.pb(nodes[st]);
    while(nxt[st] != -1) {
        st = nxt[st];
        ret.pb(nodes[st]);
    }
    return ret;
} 

void shift(vi &init) {
    int m = sz(init);
    vi nxt(m);
    for (int i = 0; i < m - 1; i++) {
        nxt[i] = i + 1;
    }
    nxt[m - 1] = -1;
    for (int i = m - 1; i >= 1; i--) {
        if(can[init[i]][init[0]]) {
            nxt[0] = nxt[i];
            nxt[i] = 0;
            break;
        }
    }
    vi ret;
    int st = 1;
    ret.pb(init[st]);
    while (nxt[st] != -1) {
        st = nxt[st]; 
        ret.pb(init[st]);
    }
    init = ret;
}

void dfs1(int v) {
    used[v] = true;
    for (int i = 0; i < n; i++) {
        if (!used[i] && i != v && can[v][i]) {
            dfs1(i);
        }
    }
    order.pb(v);
}

int cnt = 1;

void dfs2(int v) {
    used[v] = true;
    scc_num[v] = cnt;
    scc_sz[scc_num[v]]++;
    scc_val[cnt].pb(v);
    for (int i = 0; i < n; i++) {
        if (!used[i] && i != v && can[i][v]) {
            dfs2(i);
        }
    }
}

void dfs3(int v) {
    used[v] = true;
    for (int to : scc_adj[v]) {
        if (!used[to]) {
            dfs3(to);
        }
    }
    order.pb(v);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            int x; cin >> x;
            if(x) {
                can[j][i] = true;
                ed.pb(mp(j, i));
            }
            else {
                can[i][j] = true;
                // ps(i + 1, j + 1);
                ed.pb(mp(i, j));
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            dfs1(i);
        }
    }
    memset(used, false, sizeof(used));
    reverse(all(order));
    for (int i = 0; i < n; i++) {
        if (!used[order[i]]) {
            dfs2(order[i]);
            ++cnt;
        }
    }
    for (pi cur : ed) {
        scc_adj[scc_num[cur.f]].insert(scc_num[cur.s]);
    }
    ed.clear();
    memset(used, false, sizeof(used));
    order.clear();
    for (int i = 0; i < n; i++) {
        if (!used[scc_num[i]]) {
            dfs3(scc_num[i]);
        }
    }
    for (int x : order) {
        vi cvals;
        for (int curr : scc_val[x]) {
            cvals.pb(curr);
        }
        vi fpath = solve(cvals);
        pre[x] = -1;
        for (int to : scc_adj[x]) {
            if (ans[to] > ans[x]) {
                ans[x] = ans[to];
                pre[x] = to;
            }
        }
        vi cpath;
        set<int> oks;
        for (int i = 0; i < sz(fpath); i++) {
            oks.insert(fpath[i]);
        }
        while(sz(oks)){
            for (int _x : fpath) {
                cpath.pb(_x);
            }
            if (pre[x] != -1) {
                for (int _x : rets[scc_val[pre[x]][0]]) {
                    cpath.pb(_x);
                }
            }
            rets[fpath[0]] = cpath;
            oks.erase(fpath[0]);
            shift(fpath);
            cpath.clear();
        }
        ans[x] += scc_sz[x];
    }
    for (int i = 0; i < n; i++) {
        cout << ans[scc_num[i]] << ' ';
        for (int x : rets[i]) {
            cout << x + 1 << " ";
        }
        cout << '\n';
    }
}
