#include <bits/stdc++.h> 
using namespace std;

typedef long long ll;

#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)

#define F first
#define S second

const int BASE = 5058461;
const int MX = 1000005;
const int MOD = (int)(1e9 + 7);
const int MOD2 = (int) (1000696969);

ll pow2[MX];
ll pw[MX];
ll dp[MX][26];

void Innit() {
    pw[0] = 1;
    pow2[0] = 1;
    F0R(i, 1, MX) {
        pw[i] = (pw[i - 1] * BASE) % MOD2;
        pow2[i] = (pow2[i - 1] * 2) % MOD;
    }
}

void Precomp(string &s, vector<ll> &v) {
    v.push_back(s[0] - 'a');
    F0R(i, 1, (int) s.size()) {
        v.push_back((((v.back() * BASE) % MOD2) + (s[i] - 'a')) % MOD2);
    }
}

ll Query(int l, int r, vector<ll> &v) {
    if (l == 0) return v[r];
    else {
        ll ret = v[r] - (v[l - 1] * (ll) pw[r - l + 1]) % MOD2;
        if (ret < 0) ret += MOD2;
        return ret;
    }
}

int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, q; cin >> n >> q;
    Innit();
    string s, t; cin >> s >> t;
    FOR(i, n) {
        dp[i][t[i] - 'a']++;
        FOR(j, 26) {
            dp[i][j] = (dp[i][j] + 2 * (!i ? 0 : dp[i - 1][j])) % MOD;
        }
    }
    FOR(tc, q) {
        int k; string w;
        cin >> k >> w;
        vector<ll> whsh;
        Precomp(w, whsh);
        string g = s;
        int z = 0;
        ll ans = 0;
        while ((int) g.size() < (int) w.size() && z <= k) {
            g = g + t[z++] + g;
        }
        if (k < z) {
            cout << 0 << '\n';
            continue;
        }
        vector<ll> ghsh;
        Precomp(g, ghsh);
        int gsz = (int) g.size();
        int wsz = (int) w.size();
        ll ways = 0;
        FOR(i, gsz - wsz + 1) {
            if (Query(i, i + wsz - 1, ghsh) == Query(0, wsz - 1, whsh)) {
                ++ways;
            }
        }
        ans += (ways * pow2[k - z]) % MOD;
        ans %= MOD;
        vector<ll> cnt(26);
        FOR(mid, wsz) {
            int need = (w[mid] - 'a');            
            if ((mid == 0 || (Query(0, mid - 1, whsh) == Query(gsz - mid, gsz - 1, ghsh))) && 
                    (mid == wsz - 1 || (Query(mid + 1, wsz - 1, whsh) == Query(0, wsz - mid - 2, ghsh)))) {
                ++cnt[need];
            }
        }
        FOR(i, 26) {
            ans += (cnt[i] * (k == 0 ? 0 : dp[k - 1][i])) % MOD, ans %= MOD;
        }
        FOR(i, z) {
            ans -= ((cnt[(t[i] - 'a')] * pow2[k - i - 1]) % MOD);
            if (ans < 0) ans += MOD;
        }
        cout << ans << '\n';
    }
}

