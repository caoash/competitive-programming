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
    int n; cin >> n;
    vi a(n);
    vi cnt(n + 1);
    for (int i = 0; i < n; i++) {
        cin >> a[i]; 
        cnt[a[i]]++;
        if (cnt[a[i]] - 1 > n - cnt[a[i]]) {
            cout << -1 << '\n';
            return;
        }
    }
    int ans = 0;
    if (a[0] == a[n - 1]) ++ans;
    for (int i = 0; i < n - 1; i++) if (a[i] == a[i + 1]) ++ans;
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

