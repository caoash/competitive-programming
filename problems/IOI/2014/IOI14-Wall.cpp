/*
 * Have an upper and lower bound on the possible values, and merge them with lazy segment tree.
 */

#include <bits/stdc++.h> 
#include "wall.h"
using namespace std;

using ll = long long;

using vi = vector<int>;
using vl = vector<ll>;
#define pb push_back
#define rsz resize
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using pi = pair<int,int>;
#define f first
#define s second
#define mp make_pair

const int MX = 2000005;
const int MOD = (int) (1e9 + 7);
const ll INF = (ll) 1e18;

int upb[4 * MX], lowb[4 * MX];

void amx(int v, int x) {
    lowb[v] = max(lowb[v], x); 
    upb[v] = max(upb[v], lowb[v]);
}

void amn(int v, int x) {
    upb[v] = min(upb[v], x);
    lowb[v] = min(lowb[v], upb[v]);
}

void prop(int v) {
    amx(2 * v + 1, lowb[v]);
    amx(2 * v + 2, lowb[v]);
    amn(2 * v + 1, upb[v]);
    amn(2 * v + 2, upb[v]);
    lowb[v] = 0;
    upb[v] = INT_MAX;
}

void update(int v, int l, int r, int ul, int ur, int t, int h) {
    if (l != r) prop(v);
    if (ul > r || ur < l) {
        return;
    } else if (ul <= l && ur >= r) {
        if (t) {
            amn(v, h);
        } else {
            amx(v, h);
        }
        if (l != r) prop(v);
    } else {
        int m = (l + r) / 2;
        update(2 * v + 1, l, m, ul, ur, t, h);
        update(2 * v + 2, m + 1, r, ul, ur, t, h);
        return;
    }
}

int query(int v, int l, int r, int i) {
    if (l != r) prop(v);
    if (l == r) {
        return lowb[v];
    } else {
        int m = (l + r) / 2;
        if (m >= i) {
            return query(2 * v + 1, l, m, i);
        } else {
            return query(2 * v + 2, m + 1, r, i);
        }
    }
}

void buildWall(int n, int k, int op[], int left[], int right[], int height[], int finalHeight[]) {
    for (int i = 0; i < 4 * n; i++) {
        lowb[i] = 0;
        upb[i] = INT_MAX;
    }
    for (int i = 0; i < k; i++) {
        update(0, 0, n - 1, left[i], right[i], op[i] - 1, height[i]);
    }
    for (int i = 0; i < n; i++) finalHeight[i] = query(0, 0, n - 1, i);
}
