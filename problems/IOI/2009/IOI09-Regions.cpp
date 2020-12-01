/*
 * Divide regions into two groups, <= sqrt(n) and > sqrt(n). Then, answer queries using fenwick tree + small to large merging.
 */

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

const int MX = 200005;
const int MOD = (int) (1e9 + 7);
const ll INF = (ll) 1e18;

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

const int B = 500;
const int MXR = 25005;

vi adj[MX];
int nr[MX], p[MX], good[MX], st[MX], sz[MX];
int cnt = 0;
BIT<int, MX> orz;
vi locs[MX];
map<int, int> vals[MX];
map<pi, int> pre;

void dfs_init(int v, int p) {
    st[v] = cnt++;
    sz[v] = 1;
    for (int to : adj[v]) {
        if (to != p) {
            dfs_init(to, v);
            sz[v] += sz[to];
        }
    }
}

void comb(map<int, int> &a, map<int, int> &b) {
    if (sz(a) < sz(b)) swap(a, b);
    for (auto x : b) a[x.f] += x.s;
    b.clear();
}

void dfs_merge(int v, int p) {
    if (good[nr[v]]) vals[v][nr[v]]++;
    for (int to : adj[v]) {
        if (to != p) {
            dfs_merge(to, v);
            comb(vals[v], vals[to]);
        }
    }
    if (!good[nr[v]]) {
        for (auto x : vals[v]) {
            pre[mp(nr[v], x.f)] += x.s;
        }
    }
}

void dfs_path(int v, int p, map<int, int> &curr) {
    for (auto x : curr) {
        pre[mp(x.f, nr[v])] += x.s;
    }
    if (good[nr[v]]) curr[nr[v]]++;
    for (int to : adj[v]) {
        if (to != p) {
            dfs_path(to, v, curr);
        }
    }
    if (good[nr[v]]) {
        curr[nr[v]]--;
        if (curr[nr[v]] == 0) curr.erase(nr[v]);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, r, q; cin >> n >> r >> q;
    for (int i = 0; i < n; i++) {
        if (i) {
            cin >> p[i];
            p[i]--;
            adj[p[i]].pb(i);
        }
        cin >> nr[i];
        nr[i]--;
        good[nr[i]]++;
        locs[nr[i]].pb(i);
    }
    for (int i = 0; i < r; i++) {
        if (good[i] > B) good[i] = 1; 
        else good[i] = 0;
    }
    dfs_init(0, -1);
    dfs_merge(0, -1);
    map<int, int> init;
    dfs_path(0, -1, init);
    for (int i = 0; i < q; i++) {
        int qu, qv; cin >> qu >> qv;
        qu--, qv--;
        if (!good[qu] && !good[qv]) {
            int ret = 0;
            for (auto p : locs[qv]) {
                orz.upd(st[p] + 1, 1);
            }
            for (auto p : locs[qu]) {
                ret += orz.query(st[p] + 1, st[p] + sz[p]);
            }
            for (auto p : locs[qv]) {
                orz.upd(st[p] + 1, -1);
            }
            cout << ret << endl;
        } else {
            cout << pre[mp(qu, qv)] << endl;
        }
    }
}

