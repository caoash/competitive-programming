#include <bits/stdc++.h> 
#include <assert.h>
using namespace std;
 
typedef long long ll;
 
#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)
 
#define F first
#define S second

const int MX = 10;

template<class T, int SZ> struct BIT {
    T bit[SZ + 1];
    void upd(int p, ll x) {
        ++p;
        for (; p <= SZ; p += (p & -p)) {
            assert(p <= SZ);
            bit[p] += x;
        }
    }
    T sum(int r) {
        ++r;
        T res = 0;
        for (; r; r -= (r & -r)) {
            assert(r <= SZ);
            res += bit[r];
        }
        return res;
    }
    T query(int l, int r) {
        return sum(r) - sum(l - 1); 
    }
};

BIT<ll, MX> orz;
int p;
int mm;
int added;

void inicjuj(int m) {
    added = 0;
    mm = MX;
    p = -1;
}

void dodaj(int k) {
    ++p;
    if (p >= mm) p -= mm;
    orz.upd(p, -orz.query(p, p));
    orz.upd(p, k);
    ++added;
}

void koryguj(int i, int k) {
    int pos = p - i + 1 + mm;
    if (pos >= mm) pos -= mm;
    // assert(pos > 0 && pos <= mm);
    orz.upd(pos, k); 
}

ll suma(int i) {
    if (added == 0) return 0LL;
    i = min(i, added);
    int lst = p - i + 1;
    // assert(p >= max(lst, 1));
    ll res = orz.query(max(lst, 0), p);
    if (lst < 0) {
        res += orz.query(mm + lst, mm - 1);
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);    
    int q; cin >> q;
    inicjuj(0);
    FOR(t, q) {
        int qt; cin >> qt;
        if (qt == 1) {
            int k; cin >> k;
            dodaj(k);
        } else if (qt == 2) {
            int i, k; cin >> i >> k;
            koryguj(i, k);
        } else {
            int i; cin >> i;
            // suma(i);
            cout << suma(i) << '\n';    
        }
    }
}
