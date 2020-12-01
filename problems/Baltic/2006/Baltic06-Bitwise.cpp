/*
 * As with most problems involving maximizing some binary expression, let's go greedily from the back and toggle bits.
 * For the most significant bit, it can be on if every part of the expression can be on. Then, we can act greedily
 * and toggle:
 *  - first, the bits that must be on for some significant bit
 *  - second, if the most significant bit is still not on, toggle any bit that doesn't have to be on but can be on
 *  - then, if the bit is on, the bit is not forced, and some value can toggle it, change the value from 100... to 011...
 * the last part is very important, because if two values can be either 0 or 1, it doesn't matter which one you make 1 since
 * at the end it's just 100... and 011... 
 */
#include <bits/stdc++.h> 
using namespace std;

using ll = long long;

using vi = vector<int>;
#define pb push_back
#define rsz resize
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using pi = pair<int,int>;
#define f first
#define s second
#define mp make_pair

bool good(vector<pi> curr, int bit) {
    for (pi x : curr) {
        if (x.f & (1 << bit)) {
            return true;
        }
    }
    return false;
}

void go(vector<pi> &exp, int bit, bool ok) {
    for (auto &curr : exp) {
        if ((curr.f & (1 << bit)) && (curr.s & (1 << bit))) {
            ok = true; 
            curr.f -= (1 << bit);
            curr.s -= (1 << bit);
        }
    }
    for (auto &curr : exp) {
        if (!ok && (curr.f & (1 << bit))) {
            ok = true;
            curr.f -= (1 << bit);
            curr.s = 0;
        }
        else if((curr.f & (1 << bit))){
            curr.f = (1 << bit) - 1;
        }
    }
}

vector<pi> expr[105];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, p; cin >> n >> p;
    vi k(p);
    for (int i = 0; i < p; i++) {
        cin >> k[i];
    }
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < k[i]; j++) {
            int a, b; cin >> a >> b;
            expr[i].pb(mp(b, a));
        }
    }
    int ans = 0;
    for (int bit = 30; bit >= 0; bit--){
        int pt = 0;
        bool fok = true;
        bool bad = false;
        for (int i = 0; i < p; i++) {
            if (!good(expr[i], bit)) {
                bad = true;
            }
        }
        pt = 0;
        //cout << bit << " " << bad << '\n';
        for (int i = 0; i < p; i++) {
            go(expr[i], bit, bad);
        }
        if (!bad) {
            ans += (1 << bit);
        }
    }
    cout << ans << '\n';
}

