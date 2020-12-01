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

const int MX = 2001;

const ll INF = (ll) 1e18;
template<class T, int SZ> struct Seg{
    T tree[2 * SZ];
    T merge(T a, T b){
        return min(a, b);
    }
    void update(int v, int l, int r, int i, T x) {
        if (i > r || i < l) {
            return;
        } else if (l == r) {
            tree[v] = x;
        } else {
            int m = (l + r) / 2;
            update(2 * v + 1, l, m, i, x);
            update(2 * v + 2, m + 1, r, i, x);
            tree[v] = merge(tree[2 * v + 1], tree[2 * v + 2]);
        }
    }

    T query(int v, int l, int r, int ql, int qr) {
        if (l > qr || r < ql) {
            return INF;
        } else if (l >= ql && r <= qr) {
            return tree[v];
        } else {
            int m = (l + r) / 2;
            T a = query(2 * v + 1, l, m, ql, qr);
            T b = query(2 * v + 2, m + 1, r, ql, qr);
            return merge(a,b);
        }
    }
};

Seg<ll, 2000> trees[MX]; ll suf[MX][MX];


int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m; cin >> m >> n;
    vector<int> a(n), ps(n + 1);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]++;
    }
    for (int i = 1; i <= n; i++) {
        ps[i] = ps[i - 1] + a[i - 1];
    }
    auto qry = [&] (const int &l, const int &r) {
        return ps[r] - ps[l - 1];
    };
    ll ans = (ll) 1e18;
    for (int i = 1; i <= n; i++) {
        int k = 0, l = 0;
        vector<ll> ret(i);
        suf[i][i] = INF;
        for (int j = 0; j < i; j++) {
            suf[i][j] = INF;
            ll dpij = INF;
            if (qry(j + 1, i) - 1 > m){
                continue;
            }
            if (j == 0) {
                dpij = 0;
            }
            else {
                while (k <= j && qry(k + 1, j) - 1 > m) {
                    k++;   
                }
                l = k;
                while (l <= j && qry(j + 1, i) < qry(l + 1, j)) {
                    l++;
                }
                ll ft = suf[j][l]; 
                ll st = trees[j].query(0, 0, n, k, l - 1);
                if (ft != INF) dpij = min(dpij, ft + ps[i] - 2 * ps[j]);
                if (st != INF) dpij = min(dpij, st - ps[i] + 2 * ps[j]);
            }
            if (dpij != INF) {
                trees[i].update(0, 0, n, j, dpij - ps[j]);
                if (i == n) {
                    ans = min(ans, dpij);
                }
            } 
            ret[j] = dpij + ps[j];
        }
        for (int j = i - 1; j >= 0; j--) {
            suf[i][j] = min(ret[j], suf[i][j + 1]);
        }
    }
    cout << ans << '\n';
}