#include <bits/stdc++.h> 
using namespace std;

typedef long long ll;

#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)

#define F first
#define S second

int a[505][505];

int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m; cin >> n >> m;
    FOR(i, n) FOR(j, m) cin >> a[i][j];
    set<ll> pow;
    F0R(i, 1, 33) pow.insert(i * i * i * i);
    FOR(i, n) {
        FOR(j, m) {
            if (i != n - 1) {
                for (auto x : pow) {
                    if (((a[i][j] + x) % a[i + 1][j]) == 0) {
                        a[i + 1][j] += x;
                        break;
                    }
                }
            } 
            if (j != m - 1) {
                for (auto x : pow) {
                    if (((a[i][j + 1] + x) % a[i][j + 1]) == 0) {
                        a[i][j + 1] += x;
                        break;
                    }
                }
            }
        }
    }
    FOR(i, n) {
        FOR(j, m) {
            cout << a[i][j] << " ";
        }
        cout << '\n';
    }
}

