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
    int a, b; cin >> a >> b;
    string s; cin >> s;
    vi gaps;
    int n = sz(s);
    int curr = 0;
    int ones = 0;
    bool good = true;
    for (int i = 0; i < n; i++) {
        if (s[i] == '0') {
            ++curr;
            good = true;
        } else {
            if (ones && curr) gaps.pb(curr);
            curr = 0;
            if (good) ++ones, good = false;
        }
    }
    sort(all(gaps));
    int segs = ones;
    int ans = segs * a;
    int need = 0;
    for (auto x : gaps) {
        --segs;
        need += b * x;
        if (segs) {
            ans = min(ans, need + segs * a);
        }
        else break;
    }
    cout << ans << '\n';
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T; cin >> T;
    while (T--) {
        solve();
    }
}

