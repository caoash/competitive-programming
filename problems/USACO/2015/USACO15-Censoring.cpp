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

const int MX = 100005;
const int MOD = (int) 1000696969;
const ll INF = (ll) 1e18;

const int BASE = 69;

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
    for (int i = 2; i < MX; i++) invs[i] = (invs[i - 1] * invs[1]) % MOD;
    for (int i = 1; i < sz(s); i++) {
      mxp[i] = (mxp[i - 1] * BASE) % MOD;
      hsh[i] = (hsh[i - 1] + mxp[i] * (s[i] - 'a')) % MOD;
    }
    return;
  }

  int ghash(string s) {
    hsh[0] = s[0] - 'a';
    mxp[0] = 1;
    for (int i = 1; i < sz(s); i++) {
      mxp[i] = (mxp[i - 1] * BASE) % MOD;
      hsh[i] = (hsh[i - 1] + mxp[i] * (s[i] - 'a')) % MOD;
    }
    return hsh[sz(s) - 1];
  }

  ll qry(int l, int r) {
    ll lft = (l == 0 ? 0LL : hsh[l - 1]);
    return ((((hsh[r] - lft) + MOD) % MOD) * invs[l]) % MOD;
  }
};

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

map<int, set<int>> vals;
ll mxp[MX], hsh[MX], invs[MX];

int main(){
    freopen("censor.in", "r", stdin);
    freopen("censor.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    string s; cin >> s;
    int n; cin >> n;
    set<int> lens;
    for (int i = 0; i < n; i++) {
        string c; cin >> c;
        lens.insert(sz(c));
        Hash curr;
        vals[sz(c)].insert(curr.ghash(c));
    }
    assert(sz(lens) <= 400);
    string temp = "";
    hsh[0] = (s[0] - 'a');
    mxp[0] = 1;
    invs[0] = 1;
    invs[1] = modexpo(BASE, MOD - 2, MOD);
    auto qry = [&] (int l) {
        ll lft = (l == 0 ? 0LL : hsh[l - 1]);
        return ((((hsh[sz(temp) - 1] - lft) + MOD) % MOD) * invs[l]) % MOD;
    };
    for (int i = 0; i < sz(s); i++) {
        temp += s[i];
        int z = sz(temp) - 1;
        if (z) {
            mxp[z] = (mxp[z - 1] * BASE) % MOD;
            hsh[z] = (hsh[z - 1] + mxp[z] * (s[i] - 'a')) % MOD;
        }
        if (z > 1) invs[z] = (invs[z - 1] * invs[1]) % MOD;
        for (auto l : lens) {
            if (sz(temp) >= l) {
                int chsh = qry(sz(temp) - l);
                if (vals[l].count(chsh)) {
                    temp.resize(sz(temp) - l);
                }
            }
        }
    }
    cout << temp << '\n';
}

