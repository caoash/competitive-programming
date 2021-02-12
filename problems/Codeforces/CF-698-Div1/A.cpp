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
}

/*
 * 2 3 7
 *
 * 2x - y
 * 4x - 2y - z
 * 8x - 4y - 2z - a
 * 16x - 8y - 4z - 2a - b
 * 2x1 - x2
 * 2x3 - x4
 * 4x1 - 2x2 - 2x3 - x4
 *
 * 2 4 10 
 * 4 8 20
 *
 * 0, 2, 4, 6, 10, 16, 18
 *
 * 
 *
 *
 *
 * x1 x2 x3 x4
 *
 * ax1 + bx2 + cx3 + dx4
 *
 * 1 0 0 0
 * 0 1 0 0
 * 0 0 1 0
 * 0 0 0 1
 *
 * 1 0 0 0
 * -1 2 0 0
 * -1 -2 4 0
 * -1 -2 -4 8
 *
 * -1 2 0
 * -2 4 -1
 *
 *
 */
