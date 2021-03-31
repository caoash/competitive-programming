#include <bits/stdc++.h> 
#include <assert.h>
#include <cstring>
using namespace std;
 
typedef long long ll;
 
#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)
 
#define F first
#define S second

const int SZ = 250;

bool mat[31][SZ][SZ];

int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);    
    int n, m, k; cin >> n >> m >> k;
    vector<bool> init(n);
    FOR(i, k) {
        int x; cin >> x;
        x--;
        init[x] = true;
    }
    F0R(i, 1, 31) FOR(j, n) mat[i][j][j] = 1;
    FOR(i, m) {
        int u, v; cin >> u >> v;
        u--, v--;
        mat[0][u][v] = 1;
    }
    auto mul = [&] (bool a[SZ][SZ], bool b[SZ][SZ]) {
        bitset<SZ> c[SZ], d[SZ]; 
        FOR(i, SZ) {
            FOR(j, SZ) {
                c[i][j] = a[i][j];
                d[j][i] = b[i][j];
            }
        }
        FOR(i, SZ) FOR(j, SZ) {
            auto tmp = (c[i] & d[j]);
            a[i][j] = (tmp.count() > 0);
        }
    };
    F0R(i, 1, 31) {
        mul(mat[i], mat[i - 1]);
        mul(mat[i], mat[i - 1]);
    }
    auto worksEh = [&] (ll mid) {
        bool cmat[SZ][SZ];
        FOR(i, n) FOR(j, n) cmat[i][j] = 0;
        FOR(i, n) cmat[i][i] = 1;
        FOR(i, 31) {
            if (mid & (1LL << i)) {
                mul(cmat, mat[i]);
            }
        }
        FOR(i, n) {
            bool good = true;
            FOR(j, n) {
                if (init[j] && !cmat[j][i]) {
                    good = false;
                }
            }
            if (good) return true;
        }
        return false;
    };
    ll lo = 0, hi = 1e6;
    ll ans = -1;
    while (lo <= hi) {
        ll mid = (lo + hi) / 2;
        if (worksEh(mid)) {
            ans = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    if (ans != -1) {
        cout << "TAK\n";
        cout << ans << '\n';
    } else {
        cout << "NIE\n";
    }
}

