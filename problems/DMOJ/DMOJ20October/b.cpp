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

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, d; cin >> n >> d;
    vi a(n), pre(n);
    for (auto &x : a) cin >> x;
    for (int i = 0; i < n; i++) {
        pre[i] += a[i];
        if (i) pre[i] += pre[i - 1];
    }
    auto qry = [&] (int l, int r) {
        if (r < l) return 0;
        if (l == 0) return pre[r];
        else return pre[r] - pre[l - 1];
    };
    int cl = 0, cr = n - 1;
    for (int i = 0; i < d; i++) {
        int di; cin >> di;
        int fl = cl, fr = cl + di - 1;
        int sl = cl + di, sr = cr;
        ll s1 = qry(fl, fr), s2 = qry(sl, sr);
        if (s1 >= s2) {
            cout << s1 << '\n';
            cl = sl;
        }
        else {
            cout << s2 << '\n';
            cr = fr;
        }
    }
}

