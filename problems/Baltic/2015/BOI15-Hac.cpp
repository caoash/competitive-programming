/*
 * Notice for some move of the first player the second player can make it so the first player takes up any contiguous 
 * subarray of size (n + 1) / 2. So concatenate the array to itself and then use set to support queries of subarrays.
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

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    vi a(2 * n + 1);
    a[0] = 0;
    multiset<int> vals;
    int SZ = (n + 1) / 2;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[n + i] = a[i];
    }
    for (int i = 1; i <= 2 * n; i++) {
        a[i] += a[i - 1];
    }
    int ans = 0;
    vi ret(n + 1, INT_MAX);
    for (int i = 1; i <= 2 * n; i++) {
        if (i + SZ - 1 <= 2 * n) {
            vals.insert(a[i + SZ - 1] - a[i - 1]);
        }
        if (i > SZ) {
            vals.erase(vals.find(a[i - 1] - a[i - 1 - SZ]));
        }
        int prev = ((i - 1) % n) + 1;
        ret[prev] = min(ret[prev], *vals.begin());
    }
    for (int i = 1; i <= n; i++) {
        ans = max(ans, ret[i]);    
    }
    cout << ans << '\n';
}

