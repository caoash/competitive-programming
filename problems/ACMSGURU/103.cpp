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
using pl = pair<ll, ll>;
#define f first
#define s second
#define mp make_pair

const int MX = 305;
const int MOD = (int) (1e9 + 7);
const ll INF = (ll) 1e18;

vector<pi> adj[MX];
int init_col[MX], init_time[MX];
int per_c[MX][2];
bool vis[MX];
ll dist[MX]; 
int fr[MX];

int getCol(int node, int time) {
    if (time <= init_time[node]) {
        return init_col[node];
    } else {
        time -= init_time[node];
        time %= per_c[node][0] + per_c[node][1];
        if (time <= per_c[node][init_col[node] ^ 1]) {
            return init_col[node] ^ 1;
        } else {
            return init_col[node];
        }
    }
}

int getNext(int node, int time) {
    if (time <= init_time[node]) {
        return init_time[node] + 1;
    } else {
        int ntime = (time - init_time[node]);
        ntime %= per_c[node][0] + per_c[node][1];
        int last = per_c[node][init_col[node] ^ 1];
        if (ntime <= last) {
            return time + (last - ntime) + 1;
        } else {
            last += per_c[node][init_col[node]];
            return time + (last - ntime) + 1;
        }
    }
}

int findEarliest(int curr, int to, int time) {
    int curr_col = getCol(curr, time);
    int to_col = getCol(to, time);
    if (curr_col == to_col) return time;
    else {
        int nxt_curr = getNext(curr, time); 
        int nxt_to = getNext(to, time);
        if (nxt_curr != nxt_to) {
            return min(nxt_curr, nxt_to);
        } else {
            int nnxt_curr = getNext(curr, nxt_curr);
            int nnxt_to = getNext(to, nxt_to);
            if (nnxt_to != nnxt_curr) {
                return min(nnxt_to, nnxt_curr);
            } else {
                return -1;
            }
        }
    }
}

int main(){
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int S, D; cin >> S >> D;
    S--, D--;
    int N, M; cin >> N >> M;
    for (int i = 0; i < N; i++) {
        char c; cin >> c;
        if (c == 'P') init_col[i] = 1;
        cin >> init_time[i] >> per_c[i][0] >> per_c[i][1];
    }
    for (int i = 0; i < M; i++) {
        int u, v, w; cin >> u >> v >> w;
        u--, v--;
        adj[u].pb(mp(v, w)), adj[v].pb(mp(u, w));
    }
    priority_queue<pl, vector<pl>, greater<pl>> pq;
    pq.push(mp(1, S));
    for (int i = 0; i < N; i++) dist[i] = INF;
    memset(fr, -1, sizeof(fr));
    while (!pq.empty()) {
        pl curr = pq.top(); 
        pq.pop();
        if (vis[curr.s]) continue;
        for (pi to : adj[curr.s]) {
            if (!vis[to.f]) {
                ll arrive = findEarliest(curr.s, to.f, curr.f);
                if (arrive == -1) continue;
                if (arrive + to.s < dist[to.f]) {
                    dist[to.f] = arrive + to.s;
                    pq.push(mp(dist[to.f], to.f));
                    fr[to.f] = curr.s;
                }
            }
        }
        vis[curr.s] = true;
    }
    if (dist[D] == INF) {
        cout << 0 << '\n';
    } else {
        cout << dist[D] - 1 << '\n';
        int nod = D;
        vi ret;
        while (nod != S) {
            ret.pb(nod + 1);
            assert(fr[nod] != -1);
            nod = fr[nod];
        }
        ret.pb(nod + 1);
        reverse(all(ret));
        for (auto x : ret) cout << x << " ";
        cout << '\n';
    }
}

