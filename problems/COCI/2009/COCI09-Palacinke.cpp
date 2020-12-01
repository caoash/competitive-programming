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

const int MX = 526;
const int MOD = 5557;

template<int SZ, int MOD> struct Matrix {
    ll mat[SZ][SZ];
    int sz = SZ;
    Matrix() {
        memset(mat, 0, sizeof(mat));
    }
    Matrix operator*(const Matrix &mat2) {
        Matrix res;
        for (int i = 0; i < SZ; i++) {
            for (int j = 0; j < SZ; j++) {
                for (int k = 0; k < SZ; k++) {
                    res.mat[i][j] += mat[i][k] * mat2.mat[k][j];
                    if (res.mat[i][j] >= MOD) {
                        res.mat[i][j] %= MOD;
                    }
                }
            }
        }
        return res;
    }
    ll *operator[](const int &i) {
        return mat[i];
    }
    Matrix id() {
        Matrix nmat; 
        for (int i = 0; i < SZ; i++) {
            nmat.mat[i][i] = 1;
        }
        return nmat;
    };
    Matrix pow(Matrix &a, ll p) {
        Matrix res = id();
        while (p) {
            if (p & 1) {
                res = res * a;
            }
            a = a * a;
            p >>= 1;
        }
        return res;
    }
    vector<ll> mult_v(const vector<ll> &a, const Matrix &b) {
        assert(sz(a) == b.sz);
        vector<ll> res(sz(a));
        for (int i = 0; i < b.sz; i++) {
            for (int j = 0; j < sz(a); j++) {
                res[i] += (a[j] * b.mat[i][j]); 
                if (res[i] >= MOD) {
                    res[i] %= MOD;
                }
            }
        }
        return res;
    }
};

int n, m; 
vector<pi> adj[MX];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v; 
        string s; 
        cin >> u >> v >> s;
        int nmask = 0;
        for (int j = 0; j < sz(s); j++) {
            if (s[j] == 'B') nmask |= 1;
            else if (s[j] == 'J') nmask |= 2;
            else if (s[j] == 'M') nmask |= 4;
            else nmask |= 8;
        }
        adj[v].pb(mp(u, nmask));
    }
    ll k; cin >> k;
    auto solve = [&] (int mask) {
        Matrix<51, MOD> m1;
        vector<ll> init(51);
        init[0] = 1;
        init[1] = 1;
        m1.mat[0][0] = 1;
        for (pi to : adj[1]) {
            m1.mat[0][to.f] = 1;
            if ((to.s & mask) == 0) {
                m1.mat[0][n + to.f] = 1;
            }
        }
        for (int i = 1; i <= n; i++) {
            for (pi to : adj[i]) {
                m1.mat[i][to.f] = 1; 
                if ((to.s & mask) == 0) {
                    m1.mat[i][n + to.f] = 1;
                }
            }
        }
        for (int i = n + 1; i <= 2 * n; i++) {
            m1.mat[i][i - n] = 1; 
        }
        auto res = m1.pow(m1, k);
        vector<ll> ans = res.mult_v(init, res);
        return ans[0];
    };
    ll ans = 0;
    for (int mask = 0; mask < 16; mask++) {
        if (__builtin_popcount(mask) % 2) {
            ans -= solve(mask);
        }
        else {
            ans += solve(mask);
        }
        if (ans < 0) ans += MOD;
        ans %= MOD;
    }
    cout << ans << '\n';
}

