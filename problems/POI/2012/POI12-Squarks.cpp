/*
 * Given the first element, you can figure out the rest like so:
 * Find the earliest not satisfied sum of pairs. Then add an element so that it sums with a[0].
 * Then update all the new pairs you created and repeat. This can be done with multiset.
 *
 * Now the problem becomes, how do you find the first value?
 * Notice that the first two sums are a[0] + a[1], a[0] + a[2].
 * If you add those you get 2 * a[0] + a[1] + a[2].
 *
 * Notice also there must be some pair with a[1] + a[2]. So if you brute force that pair,
 * you can find all possible 2 * a[0] and thus find possible a[0] (only n of these).
 *
 * Then you can recover the sequence if possible.
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

int main(){
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    int m = n;
    n = (n * (n - 1)) / 2;
    vi a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(all(a));
    auto tri = [&] (int fir) {
        multiset<int> used;
        vi cur;
        for (int i = 0; i < n; i++) used.insert(a[i]);
        cur.pb(fir);
        while (sz(cur) < m) {
            if (used.empty()) goto end;
            int need = *(used.begin());
            int add = need - fir;
            for (auto x : cur) {
                if (!used.count(x + add)) goto end;
                used.erase(used.find(x + add));
            }
            cur.pb(add);
        }
        end:
        return cur;
    };
    vector<vi> ret;
    int ft = a[0] + a[1];
    vi todo;
    for (int i = 2; i < m; i++) {
        int dif = ft - a[i];
        if (dif > 0 && dif % 2 == 0) {
            int tst = dif / 2;
            if (tst <= a[0]) todo.pb(tst);
        }
    }
    todo.resize(unique(all(todo)) - todo.begin());
    for (auto x : todo) {
        vi ans = tri(x);
        if (sz(ans) == m) {
            ret.pb(ans);
        }
    }
    cout << sz(ret) << '\n';
    for (auto x : ret) {
        for (auto y : x) {
            cout << y << " ";
        }
        cout << '\n';
    }
}

