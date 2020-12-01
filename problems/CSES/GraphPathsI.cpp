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
    ll* operator[](const int &i) {
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
                // cout << "MULT" << '\n';
            }
            a = a * a;
            p = p / 2;
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

const int MOD = (int) (1e9 + 7);

Matrix<100, MOD> orz;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m; ll k; cin >> n >> m >> k;
    vector<ll> init(100);
    init[0] = 1; 
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--, v--;
        orz.mat[v][u]++;
    }
    Matrix res = orz.pow(orz, k);
    vector<ll> fin = res.mult_v(init, res);
    cout << fin[n - 1] << '\n';
}

