/*
Cheaters never win;if you lose the battle today
you win the war tomorrow;but you must win the battle with honor
https://t.me/codechefninjas (for discussion... AFTER CONTESTS no cheating allowed)
*/

#include <bits/stdc++.h>
using namespace std;

using longlong = long long;

using vectorint = vector<int>;
#define pushback push_back
#define re_size resize
#define beginend(x) begin(x), end(x)
#define intsize(x) (int)(x).size()

using pairintint = pair<int,int>;
#define primero first
#define segundo second
#define makepair make_pair

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int testcases; cin >> testcases;    
    while (testcases--) {
        int len; cin >> len;
        vectorint vals(len);
        for (int i = 0; i < len; i++) {
            cin >> vals[i];
        }
        longlong ans = 0;
        for (int i = 0; i < len - 1; i++) {
            // two adjacent elements
            int a = vals[i];
            int b = vals[i + 1];
            // swap them if one is less than the other
            if (a > b) swap(a, b);
            // keep multiply by two if need
            while (2 * a < b) {
                a *= 2;
                ++ans;
            }
        }
        cout << ans << '\n';
    }
}
