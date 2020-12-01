/*
 * Same as guska101 solution.
 */

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

int n;

int solve(vi a) {
    vi pos(n + 1);
    for (int i = 0; i < n; i++) pos[a[i]] = i;
    vi locs;
    for (int i = 0; i < n; i++) {
        locs.pb(((pos[i + 1] + (n / 2) - i) + n) % n);
        if (n % 2 == 1) {
            locs.pb(((pos[i + 1] + (n / 2 + 1) - i) + n) % n);
        }
    }
    sort(all(locs));
    int best = 0;
    for (int i = 1; i < sz(locs); i++) {
        best = max(best, (locs[i] - locs[i - 1]) / 2);
    }
    best = max(best, (n - (locs[sz(locs) - 1] - locs[0])) / 2);
    return (n / 2) - best;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    vi a(n);
    for (auto &x : a) cin >> x;
    int ans = solve(a);
    reverse(all(a));
    ans = min(ans, solve(a));
    cout << ans << '\n';
}

