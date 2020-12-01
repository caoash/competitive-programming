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

const int MX = 1000005;
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

void upd(int l, int r, int x) {
    l++, r++;
    orz.upd(l, x);
    orz.upd(r + 1, -x);
}

int qry(int i) {
    i++;
    return orz.sum(i);
}

int main(){
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m; cin >> n >> m;
    vi a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    auto relax = [&] (int i, int x) {
        int l = a[i], r = a[i + 1];
        if (l > r) swap(l, r);
        upd(l, r, x);
    };
    for (int i = 0; i < n - 1; i++) {
        relax(i, 1);
    }
    for (int i = 0; i < m; i++) {
        int qt; cin >> qt;
        if (qt == 1) {
            int j, v; cin >> j >> v;     
            j--;
            {
                if (j != 0) relax(j - 1, -1);
                if (j != n - 1) relax(j, -1);
            }
            a[j] = v;
            {
                if (j != 0) relax(j - 1, 1);
                if (j != n - 1) relax(j, 1);
            }
        } else {
            int x; cin >> x; 
            cout << qry(x) << '\n';
        }
    }
}

