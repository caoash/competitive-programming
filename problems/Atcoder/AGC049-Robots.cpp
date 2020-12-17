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
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    vi a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];
    int bad = 0;
    int best = 1e9;
    vi suf(n);
    for (int i = n - 1; i >= 0; i--) {
        suf[i] = bad;
        bool is_bad = (a[i] - b[i] <= 0 && best > a[i]);
        bad += is_bad;
        if (a[i] - b[i] > 0) best = min(best, a[i] - b[i]);
    }
    int ans = bad;
    for (int i = n - 1; i >= 0; i--) {
        if (a[i] - b[i] <= 0) {
            ans = min(ans, max(abs(a[i] - b[i]) + 1, suf[i]));
        }
    }
    cout << ans << '\n';
}

