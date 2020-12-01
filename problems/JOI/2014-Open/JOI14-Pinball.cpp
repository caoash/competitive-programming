/*
 * Fix the ending node, and then find the solution from the first and the last using DP + segtree.
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

const int MX = 300005;
const int MOD = (int) (1e9 + 7);
const ll INF = (ll) 1e18;

map<ll, int> cmp;

int m, n;
ll dp[MX][2];
ll best[MX][2];
vector<array<ll, 4>> nums;

struct Node {
    ll val;
};

template<int SZ> struct Seg {
    Node tree[4*SZ];

    Node merge(Node a, Node b){
        Node ret;
        ret.val = min(a.val, b.val);
        return ret;
    }

    void build(int v, int l, int r) {
        tree[v].val = INF;
        if (l != r) {
            int m = (l + r) / 2;
            build(2 * v + 1, l, m);
            build(2 * v + 2, m + 1, r);
        }
    }
    
    void update(int v, int l, int r, int i, ll x) {
        if (i > r || i < l) {
            return;
        } else if (l == r) {
            tree[v].val = x;
        } else {
            int m = (l + r) / 2;
            update(2 * v + 1, l, m, i, x);
            update(2 * v + 2, m + 1, r, i, x);
            tree[v] = merge(tree[2 * v + 1], tree[2 * v + 2]);
        }
    }

    Node query(int v, int l, int r, int ql, int qr) {
        if (l > qr || r < ql) {
            Node init;
            init.val = INF;
            return init;
        } else if (l >= ql && r <= qr) {
            return tree[v];
        } else {
            int m = (l + r) / 2;
            Node a = query(2 * v + 1, l, m, ql, qr);
            Node b = query(2 * v + 2, m + 1, r, ql, qr);
            return merge(a, b);
        }
    }
};

Seg<MX> orz[2];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> m >> n;
    set<ll> vals;
    vals.insert(1);
    for (int i = 0; i < m; i++) {
        ll a, b, c, d;
        cin >> a >> b >> c >> d;
        vals.insert(a);
        vals.insert(b);
        vals.insert(c);
        nums.pb({a, b, c, d});
    }
    vals.insert(n);
    int cnt = 0;
    for (auto x : vals) cmp[x] = cnt++;
    for (int i = 0; i < cnt; i++) {
        dp[i][0] = INF, dp[i][1] = INF;
    }
    dp[0][0] = 0;
    dp[0][1] = 0;
    orz[0].build(0, 0, cnt);
    orz[1].build(0, 0, cnt);
    for (int i = 0; i < cnt; i++) {
        best[i][0] = INF, best[i][1] = INF;
    }
    auto cng = [&] (int v, ll x, int c) {
        if (x < best[v][c]) {
            best[v][c] = x;
            orz[c].update(0, 0, cnt, v, x);
        }
    };
    cng(cmp[1], 0, 0);
    cng(cmp[n], 0, 1);
    for (int i = 1; i <= m; i++) {
        array<ll, 4> x = nums[i - 1];
        for (int j = 0; j < 2; j++) {
            dp[i][j] = orz[j].query(0, 0, cnt, cmp[x[0]], cmp[x[1]]).val + x[3];
            cng(cmp[x[2]], dp[i][j], j);
        }
    }
    ll ans = INF;
    for (int i = 1; i <= m; i++) {
        ans = min(ans, dp[i][0] + dp[i][1] - nums[i - 1][3]);
    }
    if (ans == INF) cout << -1 << '\n';
    else cout << ans << '\n';
}

