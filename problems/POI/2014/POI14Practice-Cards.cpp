/*
 * Segment tree storing the positions of cards at the ends = is config ok. Then you just need to check if any of them are ok at root.
 * To support updates, just naively swap the elements and recompute from the updated element to the root.
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

const int MX = 200005;

int vals[MX][2];

struct Node {
    int l, r; bool good[4];
};

Node merge(Node a, Node b) {
    Node ans;
    for (int i = 0; i < 4; i++) ans.good[i] = false;
    for (int j = 0; j < 4; j++) {
        for (int k = 0; k < 4; k++) {
            int nmask = (j & 2) | (k & 1);
            if(vals[a.r][(j & 1) > 0] <= vals[b.l][((k & 2) > 0)]) {
                ans.good[nmask] |= (a.good[j] && b.good[k]); 
            }
        }
    }
    ans.l = a.l, ans.r = b.r;
    return ans;
}

Node tree[4 * MX];

void build(int v, int l, int r) {
    if (l == r) {
        Node init;
        init.l = l, init.r = r;
        for (int i = 0; i < 4; i++) {
            if (((i & 1) > 0) ^ ((i & 2) > 0) == 0) {
                init.good[i] = true;
            }
            else {
                init.good[i] = false;
            }
        }
        tree[v] = init;
    }
    else {
        int m = (l + r) / 2;
        build(2 * v + 1, l, m);
        build(2 * v + 2, m + 1, r);
        tree[v] = merge(tree[2 * v + 1], tree[2 * v + 2]);
    }
    return;
}

void upd(int v, int l, int r, int i) {
    if (i > r || i < l) {
        return;
    }
    else if (l == r) {
        Node init;
        init.l = l, init.r = r;
        for (int j = 0; j < 4; j++) {
            if (((j & 1) > 0) ^ ((j & 2) > 0) == 0) {
                init.good[j] = true;
            }
            else {
                init.good[j] = false;
            }
        }
        tree[v] = init;
    }
    else {
        int m = (l + r) / 2;
        upd(2 * v + 1, l, m, i);
        upd(2 * v + 2, m + 1, r, i);
        tree[v] = merge(tree[2 * v + 1], tree[2 * v + 2]);
    }
    return;
}

bool ok() {
    bool ret = false;
    for (int i = 0; i < 4; i++) {
        ret |= tree[0].good[i];
    }
    return ret;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> vals[i][0] >> vals[i][1];
    }
    auto swp = [&](int i, int j) {
        swap(vals[i][0], vals[j][0]);
        swap(vals[i][1], vals[j][1]);
        upd(0, 0, n - 1, i);
        upd(0, 0, n - 1, j);
    };
    int m; cin >> m;
    build(0, 0, n - 1);
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        a--, b--; 
        swp(a, b);
        cout << (ok() ? "TAK" : "NIE") << '\n';
    }
}

