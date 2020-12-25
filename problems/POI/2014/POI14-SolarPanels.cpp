/*
 * Let's assume sl = sr and wl = wr. Then the answer is gcd(sl, wl).
 *
 * If we put ranges back, the answer becomes max sl <= x <= sr wl <= y <= wr gcd(x, y).
 *
 * Let's try to iterate over gcd(x, y) and call it g. How do you check if some g works?
 *
 * You can check that there exists some m such that sl <= m * g <= sr and same for wl and wr.
 *
 * Let's solve for sl and sr, it's the same for wl and wr.
 *
 * Moving some terms around, you get sl / g <= m <= sr / g, so there exists some integer in between sl / g and sr / g.
 *
 * This can be rephrased as ceil(sl / g) <= floor(sr / g). Let's observe that floor(sr / g) changes at each factor of sr, so it's like around sqrt times.
 *
 * Furthermore, observe that ceil(sl / g) is nondecreasing, meaning that if ceil(sl / g) <= floor(sr / g) when g isn't a divisor, it also will be when g is the largest
 * divisors smaller. This means we only need to check g that are divisors of sr.
 *
 * Iterate over all divisors of sr and check if they are good. Do the same for wr and set your answer to the maximum.
 */

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
const double EPS = 1e-6;

bool chk(int l, int r, int x) {
    double fd = ((double) (l) / (double) (x));
    double sd = ((double) (r) / (double) (x));
    return ceil(fd) <= floor(sd);
}

int main(){
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        int sl, sr, wl, wr; cin >> sl >> sr >> wl >> wr;
        int ans = 0;
        auto test = [&] (int x) {
            if (chk(sl, sr, x) && chk(wl, wr, x)) {
                ans = max(ans, x); 
            }
        };
        for (int j = 1; j * j <= sr; j++) {
            test(j);
            test(sr / j);
        }
        for (int j = 1; j * j <= wr; j++) {
            test(wr / j);
        }
        cout << ans << '\n';
    }
}

