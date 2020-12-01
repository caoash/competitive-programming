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

int fix = 2e8;
int mx = 4e8 + 5;

map<int, int> bit[2][2]; stack<int> sx[2], sy[2];

void upd(int x, int v, int a, int b) {
    x += fix; 
    for (; x < mx; x += (x & -x)) {
        bit[a][b][x] += v;
    }
}

int query(int x, int a, int b) {
    x += fix;
    int ret = 0;
    for (; x > 0; x -= (x & -x)) {
        ret += bit[a][b][x]; 
    }
    return ret;
}

int n, m;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    vi a(n + 1), b(n + 1);
    int px = 1, py = 1;
    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i];
        px += a[i], py += b[i];
    }
    for (int i = n; i > 1; i--) {
        px -= a[i], py -= b[i];
        int mn = min(px, px + a[i]), mx = max(px, px + a[i]);
        sx[0].push(mn), sx[1].push(mx);
        upd(mn, 1, 0, 0);
        upd(mx, 1, 0, 1);
        mn = min(py, py + b[i]), mx = max(py, py + b[i]);
        sy[0].push(mn), sy[1].push(mx);
        upd(mn, 1, 1, 0);
        upd(mx, 1, 1, 1);
    }
    px = 1, py = 1;
    int pt = 1, ans = 0, cng_x = 0, cng_y = 0;
    if (min(1 + a[1], 1) < 0 && max(1 + a[1], 1) > 0) ++ans;
    if (min(1 + b[1], 1) < 0 && max(1 + b[1], 1) > 0) ++ans;
    cin >> m;
    for (int i = 0; i < m; i++) {
        char qt; cin >> qt;
        if (qt == 'B') {
            if (pt == 1) {
                continue;
            }
            int va = min(px, px + a[pt]), vb = max(px, px + a[pt]);
            if (va < 0 && vb > 0) --ans;
            upd(va - cng_x, 1, 0, 0);
            upd(vb - cng_x, 1, 0, 1);
            sx[0].push(va), sx[1].push(vb);
            va = min(py, py + b[pt]), vb = max(py, py + b[pt]);
            if (va < 0 && vb > 0) --ans;
            upd(va - cng_y, 1, 1, 0);
            upd(vb - cng_y, 1, 1, 1);
            sy[0].push(va), sy[1].push(vb);
            --pt;
            px -= a[pt], py -= b[pt];
        }
        else if (qt == 'F') {
            if (pt == n) {
                continue;
            }
            int va = sx[0].top(), vb = sx[1].top();
            sx[0].pop(), sx[1].pop();
            upd(va, -1, 0, 0);
            upd(vb, -1, 0, 1);
            va = sy[0].top(), vb = sy[1].top();
            sy[0].pop(), sy[1].pop();
            upd(va, -1, 1, 0);
            upd(vb, -1, 1, 1);
            px += a[pt], py += b[pt]; 
            ++pt;
            if (min(px, px + a[pt]) < 0 && max(px, px + a[pt]) > 0) ++ans;
            if (min(py, py + b[pt]) < 0 && max(py, py + b[pt]) > 0) ++ans;
        }
        else if(qt == 'C') {
            int nx, ny; cin >> nx >> ny;
            if (min(px, px + a[pt]) < 0 && max(px, px + a[pt]) > 0) --ans;
            if (min(py, py + b[pt]) < 0 && max(py, py + b[pt]) > 0) --ans;
            cng_x += (nx - a[pt]);
            cng_y += (ny - b[pt]);
            a[pt] = nx, b[pt] = ny;
            if (min(px, px + a[pt]) < 0 && max(px, px + a[pt]) > 0) ++ans;
            if (min(py, py + b[pt]) < 0 && max(py, py + b[pt]) > 0) ++ans;
        }
        else {
            int ret = ans + query(-cng_x, 0, 0) - query(-cng_x, 0, 1) + query(-cng_y, 1, 0) - query(-cng_y, 1, 1);
            cout << ret << '\n';
        }
    }
}

