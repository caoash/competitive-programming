/*
 * Solve sail by sail in order of increasing height. Then, we take the rows with the least sails, so we need to update some prefix of a suffix.
 *
 * We can do it with fenwick tree + binary search. To keep the array sorted update like this:
 * instead of 1 2 2 2 4 5 => 2 3 3 2 4 5
 * do 1 2 2 2 4 5 => 2 2 3 3 4 5 
 * pretty much break it into 2 parts
 *
 * See CSAcademy candies for more details.
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

const int MX = 100005;

template<int SZ> struct BIT {
    int bit[SZ];
    void upd(int i, int x) {
        for (; i < SZ; i += (i & -i)) {
            bit[i] += x;
        }
    }
    ll qry(int i) {
        ll ret = 0;
        for (; i > 0; i -= (i & -i)) {
            ret += bit[i];
        }
        return ret;
    }
};

BIT<MX + 5> orz;

void upd(int l, int r) {
    l++, r++;
    orz.upd(l, 1);
    orz.upd(r + 1, -1);
}

int get(int x) {
    return orz.qry(x + 1);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    vector<pi> sails(n);
    for (int i = 0; i < n; i++) {
        cin >> sails[i].f >> sails[i].s;
    }
    sort(all(sails));
    auto getl = [&](int val) {
        int lo = 0; 
        int hi = MX - 1;
        int ans = 0;
        while(lo <= hi) {
            int mid = (lo + hi) / 2;
            int curr = get(mid);
            if (curr < val) {
                lo = mid + 1;
            }
            else {
                ans = mid;
                hi = mid - 1;
            }
        }
        return ans;
    };
    auto getr = [&](int val) {
        int lo = 0; 
        int hi = MX - 1;
        int ans = 0;
        while(lo <= hi) {
            int mid = (lo + hi) / 2;
            int curr = get(mid);
            if (curr <= val) {
                lo = mid + 1;
                ans = mid;
            }
            else {
                hi = mid - 1;
            }
        }
        return ans;
    };
    for (int i = 0; i < n; i++) {
        int cl = MX - sails[i].f, cr = cl + sails[i].s - 1;
        int val = get(cr);
        int cf = max(cl, getl(val)), cs = getr(val);
        int rem = sails[i].s;
        if (cf > cl) {
            upd(cl, cf - 1);
            rem -= (cf - cl);
        }
        upd(cs - rem + 1, cs);
    }
    ll ans = 0;
    for (int i = 0; i < MX; i++) {
        ll cv = get(i);
        ans += ((cv - 1) * cv) / 2;
    }
    cout << ans << '\n';
}

