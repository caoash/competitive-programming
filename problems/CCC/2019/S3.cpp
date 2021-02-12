#include <bits/stdc++.h> 
using namespace std;

typedef long long ll;

#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)

#define F first
#define S second

#include <bits/stdc++.h>
using namespace std;

ll rand(ll a, ll b){
    return a + rand()%(b-a+1);
}

ll grid[3][3];

int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    FOR(i, 3) FOR(j, 3) {
        string s; cin >> s;
        ll val = 0;
        if (s == "X") val = -1e9 - 1;
        else {
            val = stoi(s);
        }
        grid[i][j] = val + 1e9;
    }
    FOR(it, 1) {
        FOR(i, 3) FOR(j, 3) {
            if (i == 0) {
                if (grid[i][j] == -1) {
                    if (grid[i + 1][j] != -1 && grid[i + 2][j] != -1) {
                        grid[i][j] = grid[i + 1][j] - (grid[i + 2][j] - grid[i + 1][j]);
                    }
                }
            } else if (i == 1) {
                if (grid[i][j] == -1) {
                    if (grid[i - 1][j] != -1 && grid[i + 1][j] != -1) {
                        grid[i][j] = grid[i - 1][j] + ((grid[i + 1][j] - grid[i - 1][j]) / 2);
                    }
                }
            } else {
                if (grid[i][j] == -1) {
                    if (grid[i - 2][j] != -1 && grid[i - 1][j] != -1) {
                        grid[i][j] = grid[i - 1][j] + (grid[i - 1][j] - grid[i - 2][j]);
                    }
                }
            }
        }
        FOR(i, 3) FOR(j, 3) {
            if (j == 0) {
                if (grid[i][j] == -1) {
                    if (grid[i][j + 1] != -1 && grid[i][j + 2] != -1) {
                        grid[i][j] = grid[i][j + 1] - (grid[i][j + 2] - grid[i][j + 1]);
                    }
                }
            } else if (j == 1) {
                if (grid[i][j] == -1) {
                    if (grid[i][j - 1] != -1 && grid[i][j + 1] != -1) {
                        grid[i][j] = grid[i][j - 1] + ((grid[i][j + 1] - grid[i][j - 1]) / 2);
                    }
                }
            } else {
                if (grid[i][j] == -1) {
                    if (grid[i][j - 2] != -1 && grid[i][j - 1] != -1) {
                        grid[i][j] = grid[i][j - 1] + (grid[i][j - 1] - grid[i][j - 2]);
                    }
                }
            }
        }
    }
    FOR(i, 3) {
        FOR(j, 3) {
            grid[i][j] -= 1e9;
            cout << grid[i][j] << " "[j == 2];
        }
        cout << '\n';
    }
}

