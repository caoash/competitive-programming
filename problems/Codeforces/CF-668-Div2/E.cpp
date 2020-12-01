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

const int MX = 300005;

struct BIT {
    long long bit[MX];

    void add(int x, long long val) {
        for(int i = x; i < MX; i += i & -i){
            bit[i] += val;
        }
    }

    long long get(int x) {
        long long res = 0;
        for(int i = x; i > 0; i -= i & -i){
            res += bit[i];
        }
        return res;
    }
} bit;

vector<pi> qrys[MX]; 
int ans[MX];

void ad(int l, int r) {
    l++, r++;
    bit.add(l, 1);
    bit.add(r + 1, -1);
}

int at(int i) {
    i++;
    return bit.get(i);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, q; cin >> n >> q;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i] = (i + 1) - a[i];
    }
    for (int i = 0; i < q; i++) {
        int x, y; cin >> x >> y;
        int a = x, b = (n - y - 1);
        qrys[b].pb(mp(a, i));
    }
    for (int i = 0; i < n; i++) {
        int lo = 0; 
        int hi = i;
        int ret = -1;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            if (a[i] >= 0 && a[i] <= at(mid)) {
                lo = mid + 1;
                ret = mid;
            }
            else {
                hi = mid - 1;
            }
        }
        if(ret >= 0) ad(0, ret);
        for (pi to : qrys[i]) {
            ans[to.s] = at(to.f);
        }
    }
    for (int i = 0; i < q; i++) {
        cout << ans[i] << '\n';
    }
}

