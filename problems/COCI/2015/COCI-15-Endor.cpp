/*
 * Observe that two ants with color a and b bouncing off each other can be modeled as bouncing off each other.
 *
 * In other words, the ant going to the right retains it's color while the one going towards the left becomes color (a + b) % k.
 *
 * Then, we can sweep left to right and store the answer for each color since there aren't many of them, and shift them for every ant.
 */

#include <bits/stdc++.h> 
using namespace std;

using ll = long long;
using ld = long double;

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

vector<pair<pi, int>> vals;
ld ans[40];
ld tot[40];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, k, l; cin >> n >> k >> l;
    for (int i = 0; i < n; i++) {
        int d, b; char x; 
        cin >> d >> b >> x;
        if (x == 'D') {
            ans[b] += (l - d);
            vals.pb(mp(mp(d, b), 1));
        } else {
            vals.pb(mp(mp(d, b), 0));
        }
    }
    int prev = -1;
    int all = 0;
    for (auto &x : vals) {
        if (x.s) {
            ld ntot[40];
            for (int i = 0; i < k; i++) ntot[(i + x.f.s) % k] = tot[i]; 
            swap(tot, ntot);
            if (prev != -1) {
                tot[x.f.s] += (ld) (x.f.f - prev) / (ld) 2;
            }
            prev = x.f.f;
            all += x.f.s;
            all %= k;
        } else {
            ld add = 0;
            if (prev != -1) {
                ans[x.f.s] += (ld) (x.f.f - prev) / (ld) 2;
                add += (ld) (x.f.f - prev) / (ld) 2;
                for (int j = 0; j < k; j++) {
                    ans[(x.f.s + j) % k] += tot[j];
                    add += tot[j];
                }
            }
            ans[(all + x.f.s) % k] += (x.f.f - add);
        }
    }
    cout << fixed << setprecision(1);
    for (int i = 0; i < k; i++) {
        cout << ans[i] << '\n';
    }
}

