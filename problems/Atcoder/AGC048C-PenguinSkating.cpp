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

const int MX = 200005;
const int MOD = (int) (1e9 + 7);
const ll INF = (ll) 1e18;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N; ll L; cin >> N >> L;
    vl a, b;
    a.pb(0), b.pb(0);
    for (int i = 0; i < N; i++) {
        ll x; cin >> x;
        a.pb(x);
    }
    for (int i = 0; i < N; i++) {
        ll x; cin >> x;
        b.pb(x);
    }
    a.pb(L + 1), b.pb(L + 1);
    vl c, d;
    for (int i = 1; i < sz(a); i++) {
        c.pb(a[i] - a[i - 1] - 1);
        d.pb(b[i] - b[i - 1] - 1);
    }
    int l = 0, r = 0;
    ll sum = c[0];
    int p = 0;
    ll ans = 0;
    while (l < sz(c) && r < sz(c) && p < sz(d)) {
        if (c[l] == 0) {
            ++l;
            continue;
        }
        if (d[p] == 0) {
            ++p;
            continue;
        }
        if (sum == d[p]) {
            ans += max(r - p, 0) + max(p - l, 0);
            ++r, l = r;
            sum = 0;
            if (r < sz(c)) sum += c[r];
            ++p;
        } else {
            ++r;
            if (r < sz(c)) sum += c[r];
        }
    }
    if (sum > 0) cout << -1 << '\n';
    else cout << ans << '\n';
}

