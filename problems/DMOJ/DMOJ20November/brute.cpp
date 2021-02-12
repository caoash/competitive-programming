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
    int n, m; cin >> n >> m;
    vi b(n), d(m), c(n);
    for (int i = 0; i < n; i++) cin >> b[i];
    for (int i = 0; i < m; i++) cin >> d[i];
    sort(all(b));
    for (int i = 0 ; i < m; i++) {
        int f = -1;
        for (int j = 0; j < n; j++) {
            if (b[j] > d[i]) {
                f = j; 
                break;
            }
        }
        if (f != -1) {
            for (int j = f; j < n; j++) c[j]++; 
        }
        int ans = INT_MAX;
        for (int j = 0; j < n; j++) {
            ans = min(ans, (c[j] / (j + 1))); 
        }
        cout << ans << ' ';
    }
}
