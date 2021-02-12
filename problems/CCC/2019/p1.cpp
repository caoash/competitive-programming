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
    string s; cin >> s;
    int grid[2][2];
    grid[0][0] = 1, grid[0][1] = 2, grid[1][0] = 3, grid[1][1] = 4;
    auto hf = [&] () {
        int ngrid[2][2];
        ngrid[0][0] = grid[0][1];
        ngrid[0][1] = grid[0][0];
        ngrid[1][0] = grid[1][1];
        ngrid[1][1] = grid[1][0];
        swap(grid, ngrid);
    };
    auto vf = [&] () {
        int ngrid[2][2];
        ngrid[0][0] = grid[1][0];
        ngrid[0][1] = grid[1][1];
        ngrid[1][0] = grid[0][0];
        ngrid[1][1] = grid[0][1];
        swap(grid, ngrid);
    };
    FOR(i, s.size()) {
        if (s[i] == 'H') vf();
        else hf();
    }
    FOR(i, 2) {
        FOR(j, 2) {
            cout << grid[i][j] << " ";
        }
        cout << '\n';
    }
}

