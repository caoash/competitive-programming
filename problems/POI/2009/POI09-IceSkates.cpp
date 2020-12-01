/* 
 * Set c[i] = a[i] - b[i]. Then notice that if the max subarray sum <= d * k, then it's possible, otherwise not.
 *
 * You can use segtree to store max subarray sum with updates.
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

const int MX = 200005;
const int MOD = (int) (1e9 + 7);
const ll INF = (ll) 1e18;

ll k;

struct Node{
    int l, r;
    ll pre, suf, best, tot;
};

Node st[3 * MX]; 

Node merge(Node a, Node b){ 
    Node ret;   
    ret.l = a.l, ret.r = b.r;
    ret.pre = max(a.tot + b.pre, a.pre);
    ret.suf = max(b.tot + a.suf, b.suf);
    ret.best = max({a.best, b.best, a.suf + b.pre});
    assert(ret.pre >= 0 && ret.suf >= 0 && ret.best >= 0);
    ret.tot = a.tot + b.tot;
    return ret;
}

void pull(int v){
    st[v] = merge(st[2 * v + 1], st[2 * v + 2]);
}

void build(int v, int l, int r) { 
    if (l == r) {
        st[v].l = l, st[v].r = r;
        st[v].pre = 0LL, st[v].suf = 0LL, st[v].best = 0LL;
        st[v].tot = -k;
    } else {
        int m = (l + r) / 2;
        build(2 * v + 1, l, m); 
        build(2 * v + 2, m + 1, r);
        pull(v);
    }
}

void update(int v, int l, int r, int i, ll x){
    if(i > r || i < l){
        return;
    }
    else if(l == r) {
        st[v].l = l, st[v].r = r;
        st[v].pre = max(x, 0LL), st[v].suf = max(x, 0LL), st[v].best = max(x, 0LL);
        st[v].tot = x;
        return;
    }
    else{
        int m = (l + r) / 2;
        update(2 * v + 1, l, m, i, x);
        update(2 * v + 2, m + 1, r, i, x);
        pull(v);
    }
}

ll query(int v, int l, int r, int ql, int qr) {
    if (l > qr || r < ql) {
        return -INF;
    } else if (l >= ql && r <= qr) {
        return st[v].best; 
    } else {
        int m = (l + r) / 2;
        ll a = query(2 * v + 1, l, m, ql, qr);
        ll b = query(2 * v + 2, m + 1, r, ql, qr);
        return max(a, b);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m; ll d;
    cin >> n >> m >> k >> d;
    vl num(n, -k);
    build(0, 0, n - 1);
    ll need = k * d;
    for (int i = 0; i < m; i++) {
        int j, x; cin >> j >> x;
        j--;
        num[j] += x;
        update(0, 0, n - 1, j, num[j]);
        ll best = query(0, 0, n - 1, 0, n - 1);
        if (best <= need) {
            cout << "TAK\n";
        } else {
            cout << "NIE\n";
        }
    }
}

