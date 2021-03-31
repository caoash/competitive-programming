#include <bits/stdc++.h> 
using namespace std;
 
typedef long long ll;
 
#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)
 
#define F first
#define S second

const int BASE = 26;
const int MX = 100005;
const int MOD = 1e9 + 7;

template<int MX> struct Hash {
  ll hsh[MX], invs[MX], mxp[MX];
  ll modexpo(ll a, ll b, ll m) {
    a %= m;
    ll res = 1;
    while (b > 0) {
      if (b & 1)
        res = res * a % m;
      a = a * a % m;
      b >>= 1;
    }
    return res;
  }

  ll inv(ll b) {
    return modexpo(modexpo(BASE, b, MOD), MOD - 2, MOD);
  }

  void precomp(vector<int> &s, int x) {
    hsh[0] = (s[0] ^ x);
    mxp[0] = 1;
    invs[0] = 1;
    invs[1] = modexpo(BASE, MOD - 2, MOD);
    F0R(i, 2, (int) s.size() + 1) invs[i] = (invs[i - 1] * invs[1]) % MOD;
    F0R(i, 1, (int) s.size()) {
      mxp[i] = (mxp[i - 1] * BASE) % MOD;
      hsh[i] = (hsh[i - 1] + mxp[i] * (s[i] ^ x)) % MOD;
    }
    return;
  }

  ll qry(int l, int r) {
    if (r < l) return -1;
    ll lft = (l == 0 ? 0LL : hsh[l - 1]);
    return ((((hsh[r] - lft) + MOD) % MOD) * invs[l]) % MOD;
  }
};

Hash<MX> hsh, rev;

void Solve() {
    int n, m; cin >> n >> m;
    vector<int> a(n), b(m);
    vector<int> pre_a(n + 1), pre_b(m + 1);
    vector<int> eva(n), evb(m), oda(n), odb(m);
    FOR(i, n) cin >> a[i];
    FOR(i, m) cin >> b[i];
    F0R(i, 1, n + 1) pre_a[i] = (pre_a[i - 1] + a[i - 1]) % 2;
    F0R(i, 1, m + 1) pre_b[i] = (pre_b[i - 1] + b[i - 1]) % 2;
    hsh.precomp(pre_a, 0);
    rev.precomp(pre_a, 1);
    FOR(l, n) {
        ll fir = hsh.qry(0, n - l - 1);
        ll sec = rev.qry(l + 1, n);
        ll thir = hsh.qry(l + 1, n);
        eva[l] = (fir != sec);
        oda[l] = (fir != thir);
    }
    hsh.precomp(pre_b, 0);
    rev.precomp(pre_b, 1);
    FOR(l, m) {
        ll fir = hsh.qry(0, m - l - 1);
        ll sec = rev.qry(l + 1, m);
        ll thir = hsh.qry(l + 1, m);
        evb[l] = (fir != sec);
        odb[l] = (fir != thir);
    }
    int ans = 0;
    FOR(i, min(n, m)) {
        if ((eva[i] && evb[i]) || (oda[i] && odb[i])) {
            ans = i + 1;
        }
    }
    cout << ans << '\n';
}
 
int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);    
    int T; cin >> T;
    while (T--) {
        Solve();
    }
}

