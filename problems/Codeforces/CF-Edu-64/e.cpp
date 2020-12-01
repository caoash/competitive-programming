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

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    vi a(n);
    vi pos(n + 1);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        pos[a[i]] = i;
    }
    vi l(n), r(n);
    stack<pi> vals;
    for (int i = 0; i < n; i++) {
        while (!vals.empty() && vals.top().f < a[i]) {
            vals.pop();
        }
        if (vals.empty()) l[i] = -1;
        else l[i] = vals.top().s;
        vals.push(mp(a[i], i));
    }
    while (!vals.empty()) vals.pop();
    for (int i = n - 1; ~i; i--) {
        while (!vals.empty() && vals.top().f < a[i]) {
            vals.pop();
        }
        if (vals.empty()) r[i] = n;
        else r[i] = vals.top().s;
        vals.push(mp(a[i], i));
    }
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        if (i - l[i] < r[i] - i) {
            for (int j = l[i] + 1; j < i; j++) {
                if (pos[a[i] - a[j]] > i && pos[a[i] - a[j]] < r[i]) ++ans;
            }
        } else {
            for (int j = i + 1; j < r[i]; j++) {
                if (pos[a[i] - a[j]] > l[i] && pos[a[i] - a[j]] < i) ++ans;
            }
        }
    }
    cout << ans << '\n';
}

