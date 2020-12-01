/*
 *
 */

#include <bits/stdc++.h> 
using namespace std;

using ll = long long;

using vi = vector<int>;
using vl = vector<ll>;
#define pb push_back
#define rsz resize
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using pi = pair<int,int>;
using T = pair<pi, pi>;
#define f first
#define s second
#define mp make_pair

const int MX = 200005;
const int MOD = (int) (1e9 + 7);
const ll INF = (ll) 1e18;

struct R {
    pi a, b, c, d;
};

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

vector<R> rects;
vector<pair<int, pi>> adj[305][305];
gp_hash_table<int, int> cp[2];
gp_hash_table<int, int> rev[2];
int blocks[305][305];
int psum[305][305];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    set<int> xs, ys;
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2; 
        cin >> x1 >> y1 >> x2 >> y2;
        swap(x1, y1);
        swap(x2, y2);
        rects.pb({mp(x1, y1), mp(x1, y2), mp(x2, y1), mp(x2, y2)});
        xs.insert(x1), xs.insert(x2);
        ys.insert(y1), ys.insert(y2);
        if (x1 + 1 <= x2 - 1 && y1 + 1 <= y2 - 1) {
            xs.insert(x1 + 1), ys.insert(y1 + 1);
            xs.insert(x2 - 1), ys.insert(y2 - 1);
        }
    }
    int cnt = 0;
    for (auto v : xs) {
        rev[0][cnt] = v;
        cp[0][v] = cnt++;
    }
    cnt = 0;
    for (auto v : ys) {
        rev[1][cnt] = v;
        cp[1][v] = cnt++;
    }
    for (auto v : rects) {
        if (v.a.f + 1 <= v.d.f - 1 && v.a.s + 1 <= v.d.s - 1) {
            int x1 = cp[0][v.a.f + 1], y1 = cp[1][v.a.s + 1];
            int x2 = cp[0][v.d.f - 1], y2 = cp[1][v.d.s - 1];
            blocks[x2][y2]++;
            if (y1 != 0) blocks[x2][y1 - 1]--;
            if (x1 != 0) blocks[x1 - 1][y2]--;
            if (x1 != 0 && y1 != 0) blocks[x1 - 1][y1 - 1]++;
        }
    }
    for (int i = 300; i >= 0; i--) {
        for (int j = 300; j >= 0; j--) {
            blocks[i][j] = blocks[i + 1][j] + blocks[i][j + 1] - blocks[i + 1][j + 1] + blocks[i][j];
        }
    }
    for (int i = 0; i <= 300; i++) {
        for (int j = 0; j <= 300; j++) {
            psum[i][j] = (blocks[i][j] > 0);
            if (i != 0) psum[i][j] += psum[i - 1][j];
            if (j != 0) psum[i][j] += psum[i][j - 1];
            if (i != 0 && j != 0) psum[i][j] -= psum[i - 1][j - 1];
        }
    }
    auto query = [&] (int x1, int y1, int x2, int y2) {
        int sum = psum[x2][y2];   
        if (x1 != 0) sum -= psum[x1 - 1][y2];
        if (y1 != 0) sum -= psum[x2][y1 - 1];
        if (x1 != 0 && y1 != 0) sum += psum[x1 - 1][y1 - 1];
        return sum;
    };
    vector<pi> pts;
    auto add = [&] (pi v) {
        int nx = cp[0][v.f], ny = cp[1][v.s];
        if (!blocks[nx][ny]) {
            pts.pb(mp(nx, ny));
        }
    };
    for (auto x : rects) {
        add(x.a), add(x.b), add(x.c), add(x.d);
    }
    for (int i = 0; i < sz(pts); i++) {
        for (int j = i + 1; j < sz(pts); j++) {
            int x1 = min(pts[i].f, pts[j].f);
            int y1 = min(pts[i].s, pts[j].s);
            int x2 = max(pts[i].f, pts[j].f);
            int y2 = max(pts[i].s, pts[j].s);
            if (query(x1, y1, x2, y2) == 0) {
                int d = abs(rev[0][pts[i].f] - rev[0][pts[j].f]) + abs(rev[1][pts[i].s] - rev[1][pts[j].s]);
                adj[pts[i].f][pts[i].s].pb(mp(d, mp(pts[j].f, pts[j].s)));
                adj[pts[j].f][pts[j].s].pb(mp(d, mp(pts[i].f, pts[i].s)));
            }
        }
    }
    pi init = rects[0].a;
    auto change = [&] (int x1, int y1, int x2, int y2) {
        if (x1 <= init.f && x2 <= init.f && y1 <= init.s && y2 > init.s) {
            return true;
        }
        else if(x1 <= init.f && x2 <= init.f && y1 > init.s && y2 <= init.s) {
            return true;
        }
        return false;
    };
    auto dijkstra = [&] (int sx, int sy) {
        bool vis[305][305][2];
        int dist[305][305][2];
        for (int i = 0; i < 305; i++) {
            for (int j = 0; j < 305; j++) {
                for (int k = 0; k < 2; k++) {
                    dist[i][j][0] = 987654321;
                    dist[i][j][1] = 987654321;
                    vis[i][j][0] = false;
                    vis[i][j][1] = false;
                }
            }
        }
        priority_queue<T, vector<T>, greater<T>> pq;
        pq.push(mp(mp(0, 0), mp(sx, sy)));
        dist[sx][sy][0] = 0;
        while (!pq.empty()) {
            T curr = pq.top();
            pq.pop();
            for (auto x : adj[curr.s.f][curr.s.s]) {
                int nv = (curr.f.s + change(rev[0][curr.s.f], rev[1][curr.s.s], rev[0][x.s.f], rev[1][x.s.s])) % 2;
                pair<pi, int> to = mp(mp(x.s.f, x.s.s), nv);
                if (!vis[to.f.f][to.f.s][to.s]) {
                    if (dist[to.f.f][to.f.s][to.s] > dist[curr.s.f][curr.s.s][curr.f.s] + x.f) {
                        dist[to.f.f][to.f.s][to.s] = dist[curr.s.f][curr.s.s][curr.f.s] + x.f;
                        pq.push(mp(mp(dist[to.f.f][to.f.s][to.s], to.s), to.f));
                    }
                } 
            }
            vis[curr.s.f][curr.s.s][curr.f.s] = true;
        }
        return dist[sx][sy][1];
    };
    int ans = 987654321;
    for (auto x : pts) {
        int val = dijkstra(x.f, x.s);
        ans = min(ans, val);
    }
    cout << ans << '\n';
}
