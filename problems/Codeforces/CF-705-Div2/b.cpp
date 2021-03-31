#include <bits/stdc++.h> 
using namespace std;
 
typedef long long ll;
 
#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)
 
#define F first
#define S second

void Solve() {
    int h, m; cin >> h >> m;
    string s; cin >> s;
    string ch = s.substr(0, 2);
    string cm = s.substr(3, 2);
    int sh = (10 * (ch[0] - '0')) + (ch[1] - '0');
    int sm = (10 * (cm[0] - '0')) + (cm[1] - '0');
    map<int, int> rev;
    rev[0] = 0;
    rev[1] = 1;
    rev[2] = 5;
    rev[5] = 2;
    rev[8] = 8;
    auto good = [&] (int a, int b) {
        int fa = a / 10;
        int sa = a % 10;
        int fb = b / 10;
        int sb = b % 10;
        if (!rev.count(fa) || !rev.count(sa)) {
            return false;
        } else if (!rev.count(fb) || !rev.count(sb)) {
            return false;
        }
        int val_a = 10 * rev[sa] + rev[fa];
        int val_b = 10 * rev[sb] + rev[fb];
        if (val_b < h && val_a < m) return true;
        return false;
    };
    while (1) {
        if (good(sh, sm)) {
            if (sh < 10) cout << "0";
            cout << sh << ":";
            if (sm < 10) cout << "0";
            cout << sm << '\n';
            return;
        }
        ++sm;
        if (sm == m) {
            sm -= m;
            ++sh;
            if (sh == h) {
                sh -= h;
            }
        }
    }
}
 
int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);    
    int T; cin >> T;
    while (T--) {
        Solve();
    }
}

