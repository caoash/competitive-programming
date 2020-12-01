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

vi adj[6][26];

template < int SZ, int MOD > struct Matrix {
  ll mat[SZ][SZ];
  int sz = SZ;
  Matrix() {
    memset(mat, 0, sizeof(mat));
  }
  Matrix operator * (const Matrix & mat2) {
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
  ll * operator[](const int & i) {
    return mat[i];
  }
  Matrix id() {
    Matrix nmat;
    for (int i = 0; i < SZ; i++) {
      nmat.mat[i][i] = 1;
    }
    return nmat;
  };
  Matrix pow(Matrix & a, ll p) {
    Matrix res = id();
    while (p) {
      if (p & 1) res = res * a;
      a = a * a;
      p >>= 1;
    }
    return res;
  }
  vector < ll > mult_v(const vector < ll > & a,
    const Matrix & b) {
    assert(sz(a) == b.sz);
    vector < ll > res(sz(a));
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

const int ALPH = 26;

Matrix<131, MOD> cmat;
int cost[26][26];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll n; int m; cin >> n >> m;
    for (int i = 0; i < m; i++) {
        char a, b; int w; 
        cin >> a >> b >> w;
        int u = a - 'a', v = b - 'a';
        cost[u][v] = w, cost[v][u] = w;
    }
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            cost[i][j] = max(cost[i][j], 1);
            int w = cost[i][j];
            adj[w][i].pb(j);
            adj[w][j].pb(i);
        }
    }
    vector<ll> init(131);
    for (int i = 1; i <= ALPH; i++) {
        init[i] = 1;
    }
    for (int i = 0; i <= ALPH; i++) {
        cmat.mat[0][i] = 1;
    }
    for (int i = 1; i <= ALPH; i++) {
        for (int j = 0; j < 5; j++) {
            for (auto x : adj[j + 1][i - 1]) {
                cmat.mat[i][ALPH * j + x + 1] = 1;
            }
        }
    }
    for (int i = 1; i <= 4; i++) {
        for (int j = 1; j <= ALPH; j++) {
            cmat.mat[ALPH * i + j][ALPH * (i - 1) + j] = 1;
        }
    }
    Matrix<131, MOD> ans = cmat.pow(cmat, n + 1);
    vector<ll> ret = cmat.mult_v(init, ans);
    cout << ret[0] << '\n';
}

