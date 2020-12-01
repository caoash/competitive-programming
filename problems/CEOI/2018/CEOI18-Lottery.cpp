/*
* Observe that for some index, the amount you need to move to match doesn't change.
*
* Then you can do two pointers while maintaining a map of how much you need to shift.
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

int ans[10005][105];
vi pos[10005];
int cmp[10005];
int cnt[10005];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, l; cin >> n >> l;
    vi a(n);
    for (auto &x : a) cin >> x;
    set<int> vals;
    vals.insert(0);
    vi qrs;
    int q; cin >> q;
    for (int i = 0; i < q; i++) {
        int x; cin >> x;
        vals.insert(l - x);
        qrs.pb(x);
    }
    int c = 0;
    for (auto x : vals) cmp[x] = c, c++;
    auto upd = [&] (int i, int v) {
        for (int j = i + 1; j < n; j++) {
            if (a[i] == a[j]) {
                cnt[j - i] += v;
            }
        }
    };
    int p1 = 0, p2 = 0;
    upd(p2, 1);
    while (p1 <= p2 && p2 < n) {
        if (p2 < l - 1) {
            ++p2; 
            upd(p2, 1);
        } else {
            int good = 0;
            for (int i = 1; i < n; i++) {
                if (cnt[i] == 0) continue; 
                if (p1 + i > n - l) break;
                auto it = vals.ub(cnt[i]);
                if (it != vals.begin()) {
                    --it;
                    if (*it != 0) {
                        ans[p1][cmp[*it]]++;
                        ans[p1 + i][cmp[*it]]++;
                    }
                }
            }
            for (int i = 0; i < q; i++) {
                if (i != cmp[0]) good += ans[p1][i];
            }
            ans[p1][cmp[0]] = n - l - good;
            { // move
                ++p2;
                upd(p2, 1);
                upd(p1, -1);
                ++p1;
            }
        }
    }
    for (int i = 0; i <= n - l; i++)
    for (int j = q - 1; j >= 0; j--){
        ans[i][j] += ans[i][j + 1];
    }
    for (auto x : qrs) {
        for (int i = 0; i <= n - l; i++) {
            cout << ans[i][cmp[l - x]] << " ";
        }
        cout << '\n';
    }
}
