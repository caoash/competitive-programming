#include <bits/stdc++.h> 
using namespace std;

typedef long long ll;

#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)

#define F first
#define S second

const int MX = 100005;

namespace modOp {
    ll ad(ll a, int b, int mod) { return (a+b)%mod; }
    ll sub(ll a, int b, int mod) { return (a-b+mod)%mod; }
    ll mul(ll a, int b, int mod) { return (ll)a*b%mod; }

    ll AD(ll& a, ll b, int mod) { return a = ad(a,b,mod); }
    ll SUB(ll& a, ll b, int mod) { return a = sub(a,b,mod); }
    ll MUL(ll& a, ll b, int mod) { return a = mul(a,b,mod); }

    ll po (ll b, ll p, int mod) { return !p?1:mul(po(mul(b,b,mod),p/2,mod),p&1?b:1,mod); }
    ll inv (ll b, int mod) { return po(b,mod-2,mod); }

    ll invGeneral(ll a, ll b) { // 0 < a < b, gcd(a,b) = 1
        if (a == 0) return b == 1 ? 0 : -1;
        ll x = invGeneral(b%a,a);
        return x == -1 ? -1 : ((1-(ll)b*x)/a+b)%b;
    }
}

using namespace modOp;

int n, MOD;
vector<int> adj[MX];
ll dp_up[MX][2];
ll dp_down[MX][2];
int anc[MX];
queue<int> bfs;

void dfs(int v, int p) {
    dp_down[v][0] = 1, dp_down[v][1] = 1;
    for (int to : adj[v]) {
        if (to != p) {
            anc[to] = v;
            dfs(to, v);
            MUL(dp_down[v][0], ad(dp_down[to][0], dp_down[to][1], MOD), MOD);
            MUL(dp_down[v][1], dp_down[to][1], MOD);
        }
    }
}

int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> MOD;
    FOR(i, n - 1) {
        int u, v; cin >> u >> v;
        u--, v--;
        adj[u].push_back(v), adj[v].push_back(u);
    }
    dfs(0, -1);
    bfs.push(0);
    dp_up[0][0] = 1, dp_up[0][1] = 1;
    while (!bfs.empty()) {
        int v = bfs.front();
        bfs.pop();
        ll prodw = 1, prodb = 1;
        vector<int> child;
        for (int to : adj[v]) {
            if (to != anc[v]) {
                child.push_back(to);
                MUL(prodb, ad(dp_down[to][0], dp_down[to][1], MOD), MOD);
                MUL(prodw, dp_down[to][1], MOD);
            }
        }
        int sz = child.size();
        vector<ll> pre_w(sz), pre_b(sz), suf_w(sz), suf_b(sz);
        FOR(i, sz) {
            pre_w[i] = mul(dp_down[child[i]][1], (i == 0 ? 1 : pre_w[i - 1]), MOD);
            pre_b[i] = mul(ad(dp_down[child[i]][1], dp_down[child[i]][0], MOD), (i == 0 ? 1LL : pre_b[i - 1]), MOD);
        }
        FORD(i, sz) {
            suf_w[i] = mul(dp_down[child[i]][1], (i == sz - 1 ? 1 : suf_w[i + 1]), MOD);
            suf_b[i] = mul(ad(dp_down[child[i]][1], dp_down[child[i]][0], MOD), (i == sz - 1 ? 1LL : suf_b[i + 1]), MOD);
        }
        FOR(i, sz) {
            int to = child[i];
            ll prew = (i == 0 ? 1 : pre_w[i - 1]), preb = (i == 0 ? 1 : pre_b[i - 1]);
            ll sufw = (i == sz - 1 ? 1 : suf_w[i + 1]), sufb = (i == sz - 1 ? 1 : suf_b[i + 1]);
            dp_up[to][0] = ad(mul(dp_up[v][0], mul(preb, sufb, MOD), MOD), mul(dp_up[v][1], mul(prew, sufw, MOD), MOD), MOD);
            dp_up[to][1] = mul(dp_up[v][1], mul(prew, sufw, MOD), MOD);
            bfs.push(to);
        }
    }
    FOR(i, n) {
        ll ans = ad(mul(dp_down[i][0], dp_up[i][0], MOD), mul(dp_down[i][1], dp_up[i][1], MOD), MOD);
        SUB(ans, 1, MOD);
        cout << ans << '\n';
    }
}

