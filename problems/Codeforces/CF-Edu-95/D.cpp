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

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, q; cin >> n >> q;
    vi a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(all(a));
    multiset<int> diffs;
    set<int> coords;
    for (int i = 1; i < n; i++) diffs.insert(a[i] - a[i - 1]);
    for (int i = 0; i < n; i++) coords.insert(a[i]);
    auto get = [&] () {
        if (coords.empty()) {
            return 0;
        }
        int fs = *(--coords.end());
        int ss = *(coords.begin());
        int ans = fs - ss;
        if (sz(diffs)) {
            int bdiff = *(--diffs.end());
            ans -= bdiff;
        }
        return ans;
    };
    cout << get() << '\n';
    for (int i = 0; i < q; i++) {
        int t, x; 
        cin >> t >> x;
        if (t) {
            auto prev = coords.upper_bound(x);    
            auto nxt = coords.upper_bound(x);
            if (prev != coords.begin()) {
                --prev;
                diffs.insert(x - (*prev));
                if (nxt != coords.end()) {
                    diffs.erase(diffs.find((*nxt) - (*prev)));
                }
            }
            if (nxt != coords.end()) {
                diffs.insert((*nxt) - x);
            }
            coords.insert(x);
        }
        else {
            coords.erase(x);
            auto prev = coords.upper_bound(x);
            auto nxt = coords.upper_bound(x);
            if (prev != coords.begin()) {
                --prev;
                diffs.erase(diffs.find(x - (*prev)));
                if (nxt != coords.end()) {
                    diffs.insert((*nxt) - (*prev));
                }
            }
            if (nxt != coords.end()) {
                diffs.erase(diffs.find((*nxt) - x));
            }
        }
        cout << get() << '\n';
    } 
}

