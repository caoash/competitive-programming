#include <bits/stdc++.h> 
using namespace std;
 
typedef long long ll;
 
#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)
 
#define F first
#define S second

int siz[105][105];

void Solve() {
    int n; cin >> n;
    int len = (n / 2);
    F0R(l, 1, len + 1) {
        if (n % 2 == 0 && l == len) {
            FOR(i, len) {
                siz[i][i + l] = 0;
            }
        } else {
            FOR(i, n) {
                int lf = i;
                int rf = (i + l) % n;
                int d = 1;
                if (lf > rf) {
                    swap(lf, rf);
                    d = -1;
                }
                siz[lf][rf] = d;
            }
        }
    }
    FOR(i, n) F0R(j, i + 1, n) cout << siz[i][j] << " ";
    cout << '\n';
}
 
int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    int T; cin >> T; 
    while (T--) {
        Solve();
    }
}

/*
 * problem is, given N elements, for each pair:
 * increase both by 1
 * increase 1 by 3
 *
 * make them all the same with minimum number of operations
 *
 * it's kind of interesting that it's 3 points?
 * - 0 0 0 0
 * try to create sol for n = 4
 * 3 0 0 0
 * 3 3 0 0
 * 3 3 3 0
 * 3 3 3 3
 *
 * consider this prob:
 * are given an array, a[i] (equals N - 1).
 * you can pick two elements, a[i]--, and increase b[i] by 3
 * not useful reduction
 *
 * 3 3 3 3
 * 0 0 0 0
 *
 * 4 4 1 1 1
 * 0 0 0 0 0
 *
 * if N even, N - 1 odd.
 *
 * if N odd, you can always make all 0
 * if N even, you can always make all 1
 *
 * answer for N even is N / 2, answer for N odd is 0
 *
 * take a[i] mod 2, because you can do those for free
 *
 * then you have either a bunch of 0s and a single elem, or a bunch of 1s
 *
 * for N even, this is optimal, you can just do ties for the remaining
 * for N odd, last elem is annoying
 *
 * same!
 *
 * do all the lengths 1s, then all the length 2s, etc up to n/2
 *
 * for an operation, do [i, (i + len) % n]
 *
 * claim is, every start point will be used once
 *
 * 0 0 0 0 0
 *
 * 0 0 0 0
 *
 * 0 0 0
 *
 * 0 0 0 0 0
 */
