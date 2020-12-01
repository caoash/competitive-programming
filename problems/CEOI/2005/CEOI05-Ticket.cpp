/*
 *
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

const int MX = 30005;
const int MOD = (int) (1e9 + 7);
const ll INF = (ll) 1e18;

int main(){
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int m, l; cin >> m >> l;
    int n; cin >> n;
    vector<pi> vals(n);
    vector<bool> take(n);
    for (int i = 0; i < n; i++) {
        cin >> vals[i].f;
        vals[i].s = i + 1;
    }
    sort(all(vals));
    reverse(all(vals));
    int curr = m;
    for (int i = 0; i < n; i++) {
        if (vals[i].f + l - 1 < curr) {
            take[i] = true;
            curr = vals[i].f;
        }
    }
    curr = 0;
    for (int i = n - 1; i >= 0; i--) {
        int best = INT_MAX;
        int ind = -1;
        while (i >= 0 && !take[i]) {
            if (vals[i].f <= curr) {
                i--;
                continue;
            }
            int nmod = (vals[i].f - curr - 1) % l;
            if (nmod < best) {
                best = nmod, ind = i;
            }
            i--;
        }
        if (i < 0 || !take[i]) continue;
        int orig = (vals[i].f - curr - 1) % l;
        if (best < orig) {
            take[i] = false;
            take[ind] = true;
            curr = vals[ind].f + l - 1;
            i = ind;
        } else {
            curr = vals[i].f + l - 1; 
        }
    }
    int ret = 0;
    vector<pi> ans;
    vector<pi> gaps;
    vi rem;
    int prev = 0;
    for (int i = n - 1; i >= 0; i--) {
        if (take[i]) {
            int gap = vals[i].f - prev - 1;
            if (gap) gaps.pb(mp(prev + 1, gap));
            ans.pb(mp(vals[i].s, vals[i].f));
            ret += 2;
            prev = vals[i].f + l - 1;
        } else {
            rem.pb(vals[i].s);
        }
    }
    int gap = (m + 1) - prev - 1;
    if (gap) gaps.pb(mp(prev + 1, gap));
    sort(all(gaps));
    for (auto x : gaps) {
        int ad = x.s / l;
        if (ad && sz(rem)) {
            int st = x.f;
            for (int i = 0; i < ad; i++) {
                if (rem.empty()) break;
                int nxt = rem.back();
                ans.pb(mp(nxt, st));
                st += l;
                rem.pop_back();
                ++ret;
            }
        }
    }
    cout << ret << '\n';
    sort(all(ans), [&] (pi a, pi b) {
        return a.s < b.s;        
    });
    cout << sz(ans) << '\n';
    for (auto x : ans) {
        cout << x.f << " " << x.s << '\n';
    }
}

