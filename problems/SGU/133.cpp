#include <bits/stdc++.h> 
using namespace std;
 
typedef long long ll;
 
#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)
 
#define F first
#define S second

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

BIT<int, 16005> orz;

int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);    
    int n; cin >> n;
    map<int, int> cmp_x, cmp_y;
    vector<pair<int, int>> vals;
    set<int> x, y;
    FOR(i, n) {
        int l, r; cin >> l >> r;
        vals.push_back({l, r});
        x.insert(l), y.insert(r);
    }
    int cnt = 1;
    for (auto v : x) cmp_x[v] = cnt++;
    cnt = 1;
    for (auto v : y) cmp_y[v] = cnt++;
    sort(vals.begin(), vals.end());
    int ans = 0;
    for (auto v : vals) {
        int num = orz.query(cmp_y[v.S], cnt);
        if (num) ++ans;
        orz.upd(cmp_y[v.S], 1);
    }
    cout << ans << '\n';
}

