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
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int mn = a[0];
    vi b(n);
    for (int i = 1; i < n; i++) {
        if (a[i - 1] > a[i]) {
            if (a[i - 1] - mn > a[i]) {
                cout << "NO" << '\n';
                return;
            } else {
                b[i - 1] = (a[i - 1] - a[i]);
            }
        }
        mn = min(mn, a[i]);
    }
    mn = INT_MAX;
    int sum = 0;
    for (int i = n - 1; i >= 0; i--) {
        sum += b[i];
        if (sum > a[i]) {
            cout << "NO" << '\n';
            return;
        }
        mn = min(mn, a[i]);
    }
    cout << "YES" << '\n';
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T; cin >> T; 
    while (T--) {
        solve();
    }
}
