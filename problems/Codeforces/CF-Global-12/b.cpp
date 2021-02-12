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
    int T; cin >> T;
    while (T--) {
        int n, k; cin >> n >> k;
        vector<pi> pts(n);
        for (int i = 0; i < n; i++) {
            cin >> pts[i].f >> pts[i].s;
        }
        auto dist = [&] (pi a, pi b) {
            return abs(a.f - b.f) + abs(a.s - b.s);
        };
        int ans = -1;
        for (int i = 0; i < n; i++) {
            bool ok = true;
            for (int j = 0; j < n; j++) {
                if (i == j) continue;
                if (dist(pts[i], pts[j]) > k) {
                    ok = false;
                }
            }
            if (ok) ans = 1;
        }
        cout << ans << '\n';
    }
}

