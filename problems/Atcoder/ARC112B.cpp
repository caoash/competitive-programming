#include <bits/stdc++.h> 
using namespace std;
 
typedef long long ll;
 
#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)
 
#define F first
#define S second
 
int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);    
    ll B, C; cin >> B >> C;
    ll a, b, c, d;
    a = B - (C / 2), b = B + (C - 2) / 2;
    c = -B - (C - 1) / 2, d = -B + (C - 1) / 2;
    if (a > b) swap(a, b);
    if (c > d) swap(c, d);
    ll len = (b - a + 1) + (d - c + 1);
    if (min(b, d) >= max(a, c)) {
        len -= (min(b, d) - max(a, c) + 1);
    }
    cout << len << '\n';
}

/*
 * claim: four ways to do stuff
 *
 * a.) subt
 * b.) neg, subt
 * c.) neg, subt, neg
 * d.) subt, neg
 *
 * you get two ranges, find union
 */
