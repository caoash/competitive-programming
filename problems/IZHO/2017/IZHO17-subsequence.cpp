#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")

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

const int MX = 100005;
const int MOD = (int) (1e9 + 7);

pi dp[MX];
int best[(1 << 10)][(1 << 10)][11];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vi a(n), k(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> k[i];
    }
    for (int i = 0; i < (1 << 10); i++) {
        for (int j = 0; j < (1 << 10); j++) {
            for (int k = 0; k < 11; k++) {
                best[i][j][k] = -1;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        dp[i] = mp(1, -1);
        //get current dp
        int fmask = (a[i] >> 10);
        int smask = (a[i] & 1023);
        for (int mask = 0; mask < (1 << 10); mask++) {
            int tmask = fmask & mask;
            int rem = k[i] - __builtin_popcount(tmask);
            if (rem < 0 || rem > 10) {
                continue;
            }
            int fr = best[mask][smask][rem];
            if(fr != -1) { 
                dp[i] = max(dp[i], mp(dp[fr].f + 1, fr));
            }
        }
        //update future dp
        for (int mask = 0; mask < (1 << 10); mask++) {
            int cnt = __builtin_popcount(smask & mask);
            if(best[fmask][mask][cnt] == -1 || dp[i] > dp[best[fmask][mask][cnt]]) {
                best[fmask][mask][cnt] = i;
            }
        }
    }
    int curr = 0;
    for (int i = 0; i < n; i++) {
        if (dp[i].f > dp[curr].f) {
            curr = i;
        }
    }
    vi ret;
    while (curr != -1) {
        ret.pb(curr);
        curr = dp[curr].s;
    }
    cout << sz(ret) << '\n';
    reverse(all(ret));
    for (int i = 0; i < sz(ret); i++) {
        cout << ret[i] + 1 << " ";
    }
    cout << '\n';
}

