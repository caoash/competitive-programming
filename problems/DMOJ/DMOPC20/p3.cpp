#include <bits/stdc++.h> 
using namespace std;
 
typedef long long ll;
 
#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)
 
#define F first
#define S second

template<class T, int SZ> struct BIT {
    T bit[SZ + 1];
    void upd(int p, int x) {
        for (; p <= SZ; p += (p & -p)) bit[p] += x;
    }
    T sum(int r) {
        T res = 0;
        for (; r; r -= (r & -r)) res += bit[r];
        return res;
    }
    T query(int l, int r) {
        return sum(r) - sum(l - 1); 
    }
};

const int MX = 400005;

BIT<ll, MX> orz;
 
int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);    
    int n, m; cin >> n >> m;
    vector<pair<ll, ll>> evts;
    set<ll> ys;
    FOR(i, n) {
        ll x, y; cin >> x >> y;
        evts.push_back({x, y});
        ys.insert(y);
    }
    FOR(i, m) {
        ll x, y; cin >> x >> y;
        evts.push_back({x, -y});
        ys.insert(y);
    }
    map<ll, ll> cmp;
    ll cnt = 1;
    for (auto x : ys) {
        cmp[x] = cnt++;
    }
    sort(evts.begin(), evts.end());
    reverse(evts.begin(), evts.end());
    ll ans = 0;
    for (auto x : evts) {
        if (x.S > 0) {
            orz.upd(cmp[x.S], 1);
        } else {
            ans += orz.query(1, cmp[-x.S]); 
        }
    }
    cout << ans << '\n';
}

