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

const int MX = 500005;
const int MOD = (int) (1e9 + 7);
const ll INF = (ll) 1e18;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    vector<ll> a(n);
    for (auto &x : a) cin >> x;
    vector<ll> lops(n), rops(n), lv(n), rv(n);
    lv[0] = a[0], rv[n - 1] = a[n - 1];
    for (int i = 1; i < n; i++) {
        lops[i] += lops[i - 1];
        if (a[i] < lv[i - 1]) lops[i] += lv[i - 1] - a[i];
        lv[i] = max(a[i], lv[i - 1]);
    }
    for (int i = n - 2; i >= 0; i--) {
        rops[i] += rops[i + 1];
        if (a[i] < rv[i + 1]) rops[i] += rv[i + 1] - a[i];
        rv[i] = max(a[i], rv[i + 1]);
    }
    ll ans = INF;
    for (int i = 0; i < n; i++) {
        ll ops = 0;
        if (i == 0) {
            if (i + 1 < n) { 
                ops += rops[i + 1];
                if (a[i] < rv[i + 1]) ops += rv[i + 1] - a[i];
            }
        } else if (i == n - 1) {
            if (i - 1 >= 0) {
                ops += lops[i - 1];    
                if (a[i] < lv[i - 1]) ops += lv[i - 1] - a[i];
            }
        } else {
            ops += rops[i + 1];
            ops += lops[i - 1];
            ll best = max(lv[i - 1], rv[i + 1]);
            if (a[i] < best) ops += best - a[i];
        }
        ans = min(ans, ops);
    }
    cout << ans << '\n';
}

