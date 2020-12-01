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

const int MX = 1000005;
const int MOD = (int) (1e9 + 7);
const ll INF = (ll) 1e18;

const int BASE = 26;

struct Hash {
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

  void precomp(string s) {
    hsh[0] = s[0] - 'a';
    mxp[0] = 1;
    invs[0] = 1;
    invs[1] = modexpo(BASE, MOD - 2, MOD);
    for (int i = 2; i < sz(s); i++) invs[i] = (invs[i - 1] * invs[1]) % MOD;
    for (int i = 1; i < sz(s); i++) {
      mxp[i] = (mxp[i - 1] * BASE) % MOD;
      hsh[i] = (hsh[i - 1] + mxp[i] * (s[i] - 'a')) % MOD;
    }
    return;
  }

  ll qry(int l, int r) {
    ll lft = (l == 0 ? 0LL : hsh[l - 1]);
    return ((((hsh[r] - lft) + MOD) % MOD) * invs[l]) % MOD;
  }
};

void solve() {
    string s; cin >> s;
    int n = sz(s);
    Hash hsh;
    hsh.precomp(s);
    int pre = 0;
    int ans = 0;
    for (int i = 0; i < n / 2; i++) {
        if (hsh.qry(pre, i) == hsh.qry(n - i - 1, n - pre - 1)) {
            ans += 2; 
            pre = i + 1;
        }
    }
    if (n % 2) ++ans;
    else {
        if (pre < n / 2) ++ans;
    }
    cout << ans << '\n';
}

int main(){
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T; cin >> T;
    while (T--) {
        solve();
    }
}

