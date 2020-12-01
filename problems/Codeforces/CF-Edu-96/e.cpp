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
const ll INF = (ll) 1e18;

template<class T, int SZ> struct BIT {
    T bit[SZ + 1];
    void upd(int p, int x) {
        for (; p <= SZ; p += (p & -p)) bit[p] += x;
    }
    T sum(int r) {
        T res = 0;
        for (; r; r -= (r & -r)) res += bit[r];
        return res;
    }
    T query(int l, int r) {
        return sum(r) - sum(l - 1); 
    }
};

BIT<int, MX> orz;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    string s; cin >> s;
    vi pos[26];
    for (int i = 0; i < n; i++) pos[s[i] - 'a'].pb(i);
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        int cur = pos[s[i] - 'a'].back();
        pos[s[i] - 'a'].pop_back();
        orz.upd(cur + 1, 1);
        ans += orz.sum(cur);
    }
    cout << ans << '\n';
}
