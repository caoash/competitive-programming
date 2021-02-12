#include <bits/stdc++.h> 
using namespace std;

typedef long long ll;

#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)

#define F first
#define S second

const int MOD = 998244353;

ll fact[2000005];

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
};

ll nck(ll n, ll k) {
    return fact[n] * modexpo(fact[k] * fact[n - k] % MOD, MOD - 2, MOD) % MOD;
}

int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll d; cin >> d;
    fact[0] = 1;
    F0R(i, 1, 2e6 + 1) fact[i] = (fact[i - 1] * i) % MOD;
    cout << (nck(2 * d, d) * modexpo(2, MOD - 2, MOD)) % MOD << '\n';
}

