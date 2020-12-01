/*
Kind of like meet in the middle. Split teach number into two halves of the binary representation, and then update changing some
bits in each half separately. Then, use the other half to query, representing 4 flips as two sets of 2 flips.

Be careful about the order of loops. For some number, a[i], you should update the answer based on previous a[i] first so you 
don't get something like 1001 -> 1111 -> 1001, which isn't 4 away, it's 0.

Also, you need to precompute popcounts to speed it up. Also use random pragmas until one works.
*/

#pragma GCC optimize ("unroll-loops")

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

int dp[(1 << 20) + 1][5]; int pop[1024];

int _pop(int x){
    if(pop[x] == -1) pop[x] = __builtin_popcount(x);
    return pop[x];
}

int main(){
    freopen("aiacubiti.in", "r", stdin);
    freopen("aiacubiti.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    vi a(n);
    memset(pop, -1, sizeof(pop));
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        int fst = (a[i] >> 10);
        int sec = (a[i] & 1023);
        for (int j = 0; j < 1024; j++) {
            int cnt = _pop(sec ^ j);
            if (cnt <= 4) {
                ans += dp[(fst << 10) | j][4 - cnt];
            }
        }
        for (int j = 0; j < 1024; j++) {
            int cnt = _pop(fst ^ j);
            if (cnt <= 4) {
                dp[(j << 10) | sec][cnt]++;
            }
        }
    }
    cout << ans << '\n';
}