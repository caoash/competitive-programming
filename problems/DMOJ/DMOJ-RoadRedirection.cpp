#include <bits/stdc++.h> 
using namespace std;

typedef long long ll;

#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)

#define F first
#define S second


const int MX = 200005;

struct BIT {
    int bit[MX + 1];
    void upd(int p, int x) {
        for (; p <= MX; p += (p & -p)) bit[p] += x;
    }
    int sum(int r) {
        int res = 0;
        for (; r; r -= (r & -r)) res += bit[r];
        return res;
    }
    int query(int l, int r) {
        return sum(r) - sum(l - 1);
    }
    void upd2(int l, int r, int x) {
        upd(l, x);
        upd(r + 1, -x);
    }
};

vector<pair<int, int>> adj[MX];
vector<pair<int, int>> roads;
int dep[MX];
int dir[MX]; //0 = par->node
int st[MX], sz[MX];
BIT subt, anc;
int cnt = 0;

void dfs_init(int v, int p) {
    st[v] = cnt++;
    sz[v] = 1;
    for (auto to : adj[v]) {
        if (to.F != p) {
            dep[to.F] = dep[v] + 1;
            dir[to.F] = to.S;
            dfs_init(to.F, v);
            sz[v] += sz[to.F];
        }
    }
}

int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, q; cin >> n >> q;
    FOR(i, n - 1) {
        int u, v; cin >> u >> v;
        u--, v--;
        adj[u].push_back({v, 0});
        adj[v].push_back({u, 1});
        roads.push_back({u, v});
    }
    dfs_init(0, -1);
    dir[0] = -1;
    int sum = 0;
    FOR(i, n) {
        if (dir[i] == 1) {
            subt.upd(st[i] + 1, 1);        
            ++sum;
        } else if (dir[i] == 0) {
            // cout << "UPDATING: " << st[i] << " " << st[i] + sz[i] - 1 << '\n';
            anc.upd2(st[i] + 1, st[i] + sz[i], 1);
        }
    }
    FOR(i, q) {
        int qt; cin >> qt;
        if (qt == 1) {
            int b; cin >> b;
            b--;
            int sub = subt.query(st[b] + 1, st[b] + sz[b]) - (dir[b] == 1 ? 1 : 0);
            int out = anc.sum(st[b] + 1);
            int rest = dep[b] - out;
            // cout << "sub, out, rest, sum: " << sub << " " << out << " " << rest << " " << sum << '\n';
            cout << sub + out + (sum - rest - sub) << '\n';
        } else {
            int ind; cin >> ind;
            ind--;
            pair<int, int> &r = roads[ind];
            int x = r.F;
            if (dep[r.S] > dep[r.F]) x = r.S;
            if (dir[x] == 1) {
                subt.upd(st[x] + 1, -1);
                --sum;
            } else {
                anc.upd2(st[x] + 1, st[x] + sz[x], -1);
            }
            dir[x] ^= 1;
            if (dir[x] == 1) {
                subt.upd(st[x] + 1, 1);
                ++sum;
            } else {
                anc.upd2(st[x] + 1, st[x] + sz[x], 1);
            }
        }
    }
}

