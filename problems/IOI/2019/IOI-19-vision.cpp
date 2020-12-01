#include <bits/stdc++.h> 
#include "vision.h"

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

void construct_network(int H, int W, int K) {
    vi ups;
    for (int y = 0; y < W; y++) {
        pi st = mp(0, y);
        vi diag;
        while (st.f < H && st.s < W) {
            diag.pb(W * st.f + st.s);
            // cout << st.f << " " << st.s << '\n';
            ++st.f, ++st.s;
        }
        ups.pb(add_and({add_or(diag), add_xor(diag)})); 
    }
    reverse(all(ups));
    for (int x = 1; x < H; x++) {
        pi st = mp(x, 0);
        vi diag;
        while (st.f < H && st.s < W) {
            diag.pb(W * st.f + st.s);
            // cout << st.f << " " << st.s << '\n';
            ++st.f, ++st.s;
        }
        ups.pb(add_and({add_or(diag), add_xor(diag)}));
    }
    vi downs;
    for (int y = 0; y < W; y++) {
        pi st = mp(0, y);
        vi diag;
        while (st.f >= 0 && st.s >= 0 && st.f < H && st.s < W) {
            diag.pb(W * st.f + st.s);
            // cout << st.f << " " << st.s << '\n';
            ++st.f, --st.s;
        }
        downs.pb(add_and({add_or(diag), add_xor(diag)}));
    }
    for (int x = 1; x < H; x++) {
        pi st = mp(x, W - 1);
        vi diag;
        while (st.f >= 0 && st.s >= 0 && st.f < H && st.s < W) {
            diag.pb(W * st.f + st.s);
            // cout << st.f << " " << st.s << '\n';
            ++st.f, --st.s;
        }
        downs.pb(add_and({add_or(diag), add_xor(diag)}));
    }
    vi psup(sz(ups));
    for (int i = 0; i < sz(ups); i++) {
        if (i == 0) {
            psup[i] = add_xor({ups[i]}); 
        }
        else {
            psup[i] = add_xor({ups[i], psup[i - 1]});
        }
    }
    vi pdown(sz(downs));
    for (int i = 0; i < sz(downs); i++) {
        if (i == 0) {
            pdown[i] = add_xor({downs[i]});
        }
        else {
            pdown[i] = add_xor({downs[i], pdown[i - 1]});
        }
    }
    int upok = -1, downok = -1;
    for (int i = 0; i < sz(ups) - K; i++) {
        vi curr;
        for (int j = i; j < i + K; j++) {
            curr.pb(psup[j]);
        } 
        if (i == 0) upok = add_and(curr);
        else upok = add_or({upok, add_and(curr)});
    }
    for (int i = 0; i < sz(downs) - K; i++) {
        vi curr;
        for (int j = i; j < i + K; j++) {
            curr.pb(pdown[j]);
        } 
        if (i == 0) downok = add_and(curr);
        else downok = add_or({downok, add_and(curr)});
    }
    int NK = K + 1;
    int upok2 = -1, downok2 = -1;
    for (int i = 0; i < sz(ups) - NK; i++) {
        vi curr;
        for (int j = i; j < i + NK; j++) {
            curr.pb(psup[j]);
        } 
        if (i == 0) upok2 = add_and(curr);
        else upok2 = add_or({upok2, add_and(curr)});
    }
    for (int i = 0; i < sz(downs) - NK; i++) {
        vi curr;
        for (int j = i; j < i + NK; j++) {
            curr.pb(pdown[j]);
        } 
        if (i == 0) downok2 = add_and(curr);
        else downok2 = add_or({downok2, add_and(curr)});
    }
    if (W + H - 2 == K) {
        add_or({upok, downok});
    }
    else {
        add_and({add_or({upok, downok}), add_not(add_or({upok2, downok2}))});
    }
}
