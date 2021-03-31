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
        pair<pairintint, int> howmany;
        for (int i = 0; i < len; i++) {
            if (vals[i] % 3 == 0) {
                howmany.primero.primero++;
            } else if (vals[i] % 3 == 1) {
                howmany.primero.segundo++;
            } else {
                howmany.segundo++;
            }
        }
        int needed = len / 3;
        int ans = 0;
        if (howmany.primero.primero > needed) {
            int rem = howmany.primero.primero - needed;
            howmany.primero.segundo += rem;
            howmany.primero.primero = needed;
            ans += rem;
        }
        if (howmany.primero.segundo > needed) {
            int rem = howmany.primero.segundo - needed;
            howmany.segundo += rem;
            howmany.primero.segundo = needed;
            ans += rem;
        }
        if (howmany.segundo > needed) {
            int rem = howmany.segundo - needed;
            howmany.primero.primero += rem;
            howmany.segundo = needed;
            ans += rem;
        }
        if (howmany.primero.primero > needed) {
            int rem = howmany.primero.primero - needed;
            howmany.primero.segundo += rem;
            howmany.primero.primero = needed;
            ans += rem;
        }
        if (howmany.primero.segundo > needed) {
            int rem = howmany.primero.segundo - needed;
            howmany.segundo += rem;
            howmany.primero.segundo = needed;
            ans += rem;
        }
        if (howmany.segundo > needed) {
            int rem = howmany.segundo - needed;
            howmany.primero.primero += rem;
            howmany.segundo = needed;
            ans += rem;
        }
        cout << ans << '\n';
    }
}
