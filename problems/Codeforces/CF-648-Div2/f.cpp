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
    vi a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];
    map<pi, int> vals;
    for (int i = 0; i < n / 2; i++) {
        int x = a[i], y = a[n - i - 1];
        vals[mp(min(x, y), max(x, y))]++;
    }
    map<pi, int> sec;
    for (int i = 0; i < n / 2; i++) {
        int x = b[i], y = b[n - i - 1];
        sec[mp(min(x, y), max(x,y))]++;
    }
    for (auto &x : vals) {
        if (sec[x.f] != x.s) {
            cout << "NO" << '\n';
            return;
        }
    }
    if (n % 2 && a[n / 2] != b[n / 2]) {
        cout << "NO" << '\n';
        return;
    }
    cout << "YES" << '\n';
    return;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t; cin >> t;
    while (t--) {
        solve();
    }
}

