#include <bits/stdc++.h> 
#include "cyklib.hpp"
using namespace std;
 
typedef long long ll;
 
#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)
 
#define F first
#define S second

void interact() {
    int k = 0; 
    ll init = circular_shift(0);
    ll prev = init;
    auto les = [&] (ll x, ll y, ll fir) {
        if (x < fir && y >= fir) {
            return 0;
        } else if (y < fir && x >= fir) {
            return 1;
        } else {
            return (y > x ? 1 : 0);
        }
    };
    int mv = 1;
    while(1) {
        ll cur = circular_shift(mv);
        if (cur == prev) {
            give_answer(mv);
            return;
        } else if (les(cur, prev, init)) {
            break;
        }
        prev = cur;
        mv *= 2;
        ++k;
    }
    ll lo = 0, hi = (1LL << k);
    int ans = -1;
    while (lo <= hi) {
        ll mid = (lo + hi) / 2;
        ll cur = (1LL << k) + mid;
        ll x = cur / 2;
        ll y = (cur - x);
        init = circular_shift(0);
        ll ga = circular_shift(x); 
        ll gb = circular_shift(y);
        if (les(gb, ga, init)) {
            hi = mid - 1;
            ans = cur;
        } else {
            lo = mid + 1;
        }
    }
    give_answer(ans);
}
 
int main() {
    interact();
}

