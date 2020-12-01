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

const int MX = 200005;
const int MOD = (int) (1e9 + 7);
const ll INF = (ll) 1e18;

void solve() {
    int n; cin >> n;
    vi a(n);
    for (auto &x : a) cin >> x;
    sort(all(a));
    ll sp = 0, sn = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] > 0) sp += a[i];
        else if (a[i] < 0) sn += abs(a[i]);
    }
    if (sp == sn) {
        cout << "NO" << '\n';
        return;
    } else {
        cout << "YES" << '\n';
        if (sp > sn) {
            for (int i = 0; i < n; i++) if (a[i] > 0) cout << a[i] << " ";
            for (int i = 0; i < n; i++) if (a[i] <= 0) cout << a[i] << " ";
        } else {
            for (int i = 0; i < n; i++) if (a[i] < 0) cout << a[i] << " ";
            for (int i = 0; i < n; i++) if (a[i] >= 0) cout << a[i] << " ";
        }
        cout << '\n';
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T; cin >> T;
    while (T--) {
        solve();
    }
}

