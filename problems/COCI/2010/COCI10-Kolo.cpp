/*
 * Simulate the problem forwards to find the final position of the first guy who jumps, then you know the final positions of the last guys (i - 1, i + 1).
 *
 * Then we can run the process in reverse to find the final values of the adjacent guys because we know their final position.
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

bool prim[10000007];

int main(){
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, k, a; cin >> n >> k >> a;
    a--;
    memset(prim, true, sizeof(prim));
    prim[0] = prim[1] = false;
    vi prims;
    for (ll i = 2; i <= 1e7; i++) {
        if (prim[i]) {
            if (sz(prims) == k) break;
            prims.pb(i);
            if ((ll) (i * i) <= 1e7) {
                for (int j = i * i; j <= 1e7; j += i) {
                   prim[j] = false;
                }
            }
        }
    }
    auto Sim = [&] (int num) {
        int pos = num;
        auto Move = [&] (int inc) {
            int end = inc % n; 
            if (pos == 0) {
                pos = end;
            } else {
                int meet = pos;
                int ad = 0;
                if (inc >= meet) ad = 1, inc -= meet;
                if (inc) ad += (inc / (n - 1)) % n;
                ad %= n;
                pos -= ad;
                if (pos < 0) pos += n;
            }
        };
        for (auto p : prims) {
            Move(p);
        }
        return pos;
    };
    int fin = Sim(a);
    reverse(all(prims));
    auto Rev = [&] (int num) {
        int pos = num;
        auto Move = [&] (int dcr) {
            int end = dcr % n;
            if (pos == end) {
                pos = 0;
            } else {
                int meet = pos;
                int rem = 0;
                if ((end - meet + n) % n <= dcr) {
                    rem++;
                    dcr -= ((end - meet + n) % n);
                }
                if (dcr) rem += (dcr / (n - 1)) % n;
                rem %= n;
                pos += rem;
                if (pos >= n) pos -= n;
            }
        };
        for (auto p : prims) {
            Move(p);
        }
        return pos;
    };
    int fir = Rev((fin - 1 + n) % n);
    int sec = Rev((fin + 1) % n);
    cout << sec + 1 << " " << fir + 1 << '\n';
}

