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
    string s; cin >> s;
    int a_cnt = 0;
    FOR(i, s.size()) a_cnt += (s[i] == 'a');
    string ans = "";
    vector<int> siz;
    int cur = 0;
    FOR(i, s.size()) {
        if (s[i] == 'a') ++cur;
        else {
            if (cur) siz.push_back(cur);
            cur = 0;
        }
    }
    if (cur) siz.push_back(cur);
    if (a_cnt % 2 == 0) {
        FOR(i, s.size() - a_cnt) ans += "b";
        if (s[s.size() - 1] == 'a') {
            int suf = siz.back();
            siz.pop_back();
            int ones = 0;
            sort(siz.begin(), siz.end());
            for (auto x : siz) {
                if (x == 1) ++ones;
                else { suf += x - 2;
                }
            }
            if (ones % 2) --suf;
            FOR(i, suf) ans += "a";
        }
    } else {
        if (s[s.size() - 1] == 'a') {
            FOR(i, s.size() - a_cnt) ans += "b";
            int suf = siz.back();
            siz.pop_back();
            int ones = 0;
            sort(siz.begin(), siz.end());
            for (auto x : siz) {
                if (x == 1) ++ones;
                else {
                    suf += x - 2;
                }
            }
            if (ones % 2) --suf;
            FOR(i, suf) ans += "a";
        } else {
            int bsuf = 0;
            FORD(i, s.size()) {
                if (s[i] == 'a') break;
                else ++bsuf;
            }
            if (bsuf <= 2) {
                int last = -1;
                FOR(i, s.size()) {
                    if (s[i] == 'a') last = i;
                }
                FOR(i, s.size()) {
                    if (i == last) ans += "a";
                    else {
                        if (s[i] == 'b') ans += "b";
                    }
                }
            } else {
                if (bsuf == s.size() - a_cnt) {
                    ans += "a";
                    FOR(i, s.size() - a_cnt) ans += "b";
                } else {
                    FOR(i, s.size() - a_cnt - 2) ans += "b";
                    int tot = 0;
                    int suf = 0;
                    int ones = 0;
                    for (auto x : siz) {
                        if (x == 1) ++ones;
                        else {
                            tot += x - 2;
                        }
                    }
                    int pre = 0;
                    FOR(i, s.size()) {
                        if (s[i] == 'a') ++pre;
                        else break;
                    }
                    FOR(i, siz.size()) {
                        int x = siz[i];
                        if (pre > 0) {
                            pre = 0;
                            continue;
                        }
                        int nones = ones - (x == 1);
                        suf = max(suf, x + tot - max(x - 2, 0) - (nones % 2));
                    }
                    FOR(i, suf) ans += "a";    
                }
            }
        }
    }
    cout << ans << '\n';
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);    
    int T; cin >> T;
    while (T--) {
        Solve();
    }
}

