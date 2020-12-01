/*
 * Let dp[root][day] = maximum you can get at root up to day. A simple NK dp goes as follows:
 * dp[root][day] = max(sum of dp[child][day], sum of dp[child][d[root]] + val[root] if day >= d[root]).
 *
 * Then we can observe that the dp ends up being monotonic, and not that many days actually matter (since it's better to take a lower day with the same value over a larger day.)
 * Actually, the dates only matter when the dp is changed, which happens at most once per node. Then, to update all later dp values to max(sum of dp[child][d[root]] + val[root],
 * sum of dp[child][day]) we can break it up into consequtive differences and propogate the value of val[i].
 *
 * Key ideas:
 * - merge small to large
 * - store differences to update in monotonic set
 * - only care about interesting dp values
 *
 * Overall, very complicated but cool problem.
 */

#include <bits/stdc++.h> 
using namespace std;

using ll = long long;

using vi = vector<int>;
#define pb push_back
#define rsz resize
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using pi = pair<int,int>;
#define f first
#define s second
#define mp make_pair

const int MX = 100005;

int p[MX]; ll d[MX], w[MX]; 
map<int, ll> dp[MX];

void merge(map<int, ll> &a, map<int, ll> &b) {
    if (sz(b) > sz(a)) swap(a, b);
    for (auto &x : b) {
        a[x.f] += x.s;
    }
    b.clear();
}

void add(map<int, ll> &a, int d, int v) {
    a[d] += v;
    for (auto it = a.upper_bound(d); it != a.end() && v > 0;) {
        if ((it -> s) > v) {
            a[(it -> f)] -= v;
            break;
        }
        else {
            v -= (it -> s);
            it = next(it);
            a.erase(prev(it));
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m, k; cin >> n >> m >> k;
    for (int i = 0; i < n - 1; i++) {
        cin >> p[i + 1];
        p[i + 1]--;
    }
    memset(d, -1, sizeof(d));
    for (int i = 0; i < m; i++) {
        int x; cin >> x;
        x--;
        cin >> d[x] >> w[x];
    }
    for (int i = n; i > 0; i--) {
        if(d[i] != -1) add(dp[i], d[i], w[i]);
        merge(dp[p[i]], dp[i]);
    }
    ll ans = 0;
    for (auto x : dp[0]) {
        ans += x.s;
    }
    cout << ans << '\n';
}

