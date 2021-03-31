#include <bits/stdc++.h> 
using namespace std;
 
typedef long long ll;
 
#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)
 
#define F first
#define S second

bool win[512][2];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);    
    int k; cin >> k;
    while (k--) {
        int n, m; cin >> n >> m;
        win[1][0] = false;
        win[1][1] = true;
        int mask = 0;
        vector<int> a(m);
        FOR(i, m) {
            cin >> a[i];
            mask |= (1 << (a[i] - 2));
        }
        F0R(i, 2, 512) {
            win[i][1] = true;
            F0R(j, 1, 10) {
                if (i - j <= 0) continue;
                if (j == 1 || mask & (1 << (j - 2))) {
                    if (!win[i - j][0]) {
                        win[i][1] = false;
                    }
                }
            }
            win[i][0] = false;
            F0R(j, 1, 10) {
                if (i - j <= 0) continue;
                if (j == 1 || (mask & (1 << (j - 2)))) {
                    if (win[i - j][1]) {
                        win[i][0] = true;
                    }
                }
            }
        }
        bool done = false;
        FOR(offset, 512) {
            F0R(len, 1, 512) {
                bool good = true;
                F0R(pos, offset, offset + len) {
                    F0R(test, 1, 10) {
                        if (win[pos][0] != win[pos + (len * test)][0]) {
                            good = false; 
                        }
                    }
                }
                if (good) {
                    if (n <= offset) {
                        cout << (win[n][0] ? "FIRST PLAYER MUST WIN" : "SECOND PLAYER MUST WIN") << '\n';
                    } else {
                        cout << (win[((n - offset) % len) + offset][0] ? "FIRST PLAYER MUST WIN" : "SECOND PLAYER MUST WIN") << '\n';
                    }
                    done = true;
                    break;
                }
            }
            if (done) break;
        }
    }
}

