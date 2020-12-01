/*
 * Do HLD but merge the HLDs small to large. When merging two trees, add a light edge between them. This means each operation adds at most one "move" to each query.
 *
 * Then, we can rebuild the HLD every sqrt(Q) operations. This means that each operation does at most sqrt(Q) extra moves, and you rebuild it at most sqrt(Q) times.
 *
 * Merging HLDs small to large works because each node will be rebuilt at most logN times. To make implementation easier, just put all of the preorders together into
 * a single BIT, since it fits into the ML. It doesn't matter if the whole preorder is correct, only that the preorder in a heavy path are adjacent which stays true.
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

const int MX = 30005;
const int HUGE = 3000000;
const int MOD = (int) (1e9 + 7);
const ll INF = (ll) 1e18;

template < int SZ > struct DSU {
  int p[SZ], sz[SZ];
  void init() {
    for (int i = 0; i < SZ; i++) {
      p[i] = i;
      sz[i] = 1;
    }
  }
  int find(int x) {
    return p[x] = (p[x] == x ? x : find(p[x]));
  }
  void merge(int u, int v) {
    int a = find(u);
    int b = find(v);
    if (a != b) {
      if (sz[a] < sz[b]) {
        swap(a, b);
      }
      p[b] = a;
      sz[a] += sz[b];
    }
  }
};

template<class T, int SZ> struct BIT {
    T bit[SZ + 1];
    void upd(int p, int x) {
        for (; p <= SZ; p += (p & -p)) bit[p] += x;
    }
    T sum(int r) {
        T res = 0;
        for (; r; r -= (r & -r)) res += bit[r];
        return res;
    }
    T query(int l, int r) {
        return sum(r) - sum(l - 1); 
    }
};

int head[MX], anc[MX], sub[MX], dep[MX], st[MX];
int dat[MX];
vi adj[MX];
DSU<MX> conn;
BIT<int, HUGE> orz;
int n;

int cnt = 1;

void dfs_sz(int v) {
    sub[v] = 1;
    for (int &to : adj[v]) {
        if (to == anc[v]) swap(to, adj[v][sz(adj[v]) - 1]);
    }
    for (int &to : adj[v]) {
        if (to != anc[v]) {
            anc[to] = v;
            dep[to] = dep[v] + 1;
            dfs_sz(to);
            sub[v] += sub[to]; 
            if (sub[to] > sub[adj[v][0]]) {
                swap(to, adj[v][0]);
            }
        }
    }
}

void dfs_hld(int v) {
    st[v] = cnt++;
    orz.upd(st[v], dat[v]);
    for (int to : adj[v]) {
        if (to != anc[v]) {
            head[to] = (to == adj[v][0] ? head[v] : to);
            dfs_hld(to);
        }
    }
}

int query(int a, int b) {
    int ret = 0;
    while (head[a] != head[b]) {
        if (dep[head[b]] > dep[head[a]]) swap(a, b);
        ret += orz.query(st[head[a]], st[a]);
        a = anc[head[a]];
    }
    if (dep[b] > dep[a]) swap(a, b);
    ret += orz.query(st[b], st[a]);
    return ret;
}

void upd(int v, int x) {
    orz.upd(st[v], -dat[v]);
    dat[v] = x;
    orz.upd(st[v], dat[v]);
}

int eds = 0;

void merge(int u, int v) {
    int a = conn.find(u);
    int b = conn.find(v);
    if (conn.sz[a] > conn.sz[b]) swap(u, v);
    conn.merge(u, v);
    anc[u] = v;
    dep[u] = dep[v] + 1;
    head[u] = u;
    adj[u].pb(v), adj[v].pb(u);
    dfs_sz(u);
    dfs_hld(u);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> dat[i];        
        orz.upd(i + 1, dat[i]);
        st[i] = i + 1;
        anc[i] = -1;
        head[i] = i;
        ++cnt;
    }
    conn.init();
    int q; cin >> q;
    int times = 0;
    for (int i = 0; i < q; i++) {
        string qt; cin >> qt;
        if (qt == "bridge") {
            int u, v; cin >> u >> v;    
            u--, v--;
            if (conn.find(u) == conn.find(v)) {
                cout << "no" << endl;
            } else {
                merge(u, v);
                ++times;
                if ((times % 300) == 0) {
                    dep[u] = 0;
                    head[u] = u;
                    anc[u] = -1;
                    dfs_sz(u);
                    dfs_hld(u);
                }
                cout << "yes" << endl;
            }
        } else if (qt == "penguins") {
            int u, x; cin >> u >> x;
            u--;
            upd(u, x);
        } else {
            int u, v; cin >> u >> v;
            u--, v--;
            if (conn.find(u) != conn.find(v)) {
                cout << "impossible" << endl;
            } else {
                cout << query(u, v) << endl;
            }
        }
    }
}
