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

void solve() {
    int n; ll w;
    cin >> n >> w;
    vl a(n);
    vector<pair<ll, int>> smal, med;
    ll need = (w + 1) / 2;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (a[i] > w) continue;
        else if (a[i] >= need) {
            med.pb(mp(a[i], i));
        } else {
            smal.pb(mp(a[i], i));
        }
    }
    if (sz(med) > 0) {
        cout << 1 << '\n';
        cout << med[0].s + 1 << '\n';
        return;
    } else {
        ll sum = 0;
        vi ans;
        for (int i = 0; i < sz(smal); i++) {
            sum += smal[i].f;
            ans.pb(smal[i].s + 1);
            if (sum >= need) break;
        }
        if (sum >= need) {
            cout << sz(ans) << '\n';
            for (int x : ans) cout << x << " ";
            cout << '\n';
        } else {
            cout << -1 << '\n';
        }
    }
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

