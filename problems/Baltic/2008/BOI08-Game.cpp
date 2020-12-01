/*
 * Naive game theory DP is dp[x1][y1][x2][y2][turn] = can p1 win.
 *
 * Then, observe that they only want to move along shortest paths, so the game theory graph becomes acyclic!
 *
 * To optimize it, realize that a lot of pairs of squares can't really happen. Do dp[time][i1][i2] where i1 and i2 are indexes
 * in the lists of where each player can be at time.
 *
 * Finally, you need to do some additional memory optimizations to get AC.
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
#define f first
#define s second
#define mp make_pair
 
const int MX = 300;
const int MOD = (int) (1e9 + 7);
const ll INF = (ll) 1e18;
 
namespace output {
    void pr(int x) { cout << x; }
    void pr(long x) { cout << x; }
    void pr(ll x) { cout << x; }
    void pr(unsigned x) { cout << x; }
    void pr(unsigned long x) { cout << x; }
    void pr(unsigned long long x) { cout << x; }
    void pr(float x) { cout << x; }
    void pr(double x) { cout << x; }
    void pr(long double x) { cout << x; }
    void pr(char x) { cout << x; }
    void pr(const char* x) { cout << x; }
    void pr(const string& x) { cout << x; }
    void pr(bool x) { pr(x ? "true" : "false"); }
    
    template<class T1, class T2> void pr(const pair<T1,T2>& x);
    template<class T> void pr(const T& x);
    
    template<class T, class... Ts> void pr(const T& t, const Ts&... ts) { 
        pr(t); pr(ts...); 
    }
    template<class T1, class T2> void pr(const pair<T1,T2>& x) { 
        pr("{",x.f,", ",x.s,"}"); 
    }
    template<class T> void pr(const T& x) { 
        pr("{"); // const iterator needed for vector<bool>
        bool fst = 1; for (const auto& a: x) pr(!fst?", ":"",a), fst = 0; 
        pr("}");
    }
    
    void ps() { pr("\n"); } // print w/ spaces
    template<class T, class... Ts> void ps(const T& t, const Ts&... ts) { 
        pr(t); if (sizeof...(ts)) pr(" "); ps(ts...); 
    }
    
    void pc() { cout << "]" << endl; } // debug w/ commas
    template<class T, class... Ts> void pc(const T& t, const Ts&... ts) { 
        pr(t); if (sizeof...(ts)) pr(", "); pc(ts...); 
    }
    #define dbg(x...) pr("[",#x,"] = ["), pc(x);
}
 
#ifdef LOCAL
using namespace output;
#else
#define dbg(x...) 4
#endif
 
const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, 1, 0, -1};
 
int n;
pi sa, sb;
bool blocked[MX][MX];
int dist[MX][MX][2];
bool used[MX][MX][2];

bool dp[2][2 * MX][2 * MX];

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
 
pi pos[MX][MX][2];
int cnt[MX * MX][2];
vector<pi> vals[MX * MX][2];

bool valid(int x, int y) {
    return x >= 0 && y >= 0 && x < n && y < n && !blocked[x][y];
}
 
void solve() {
    cin >> n;
    memset(dist, 0x3f3f3f, sizeof(dist));
    memset(used, false, sizeof(used));
    memset(cnt, 0, sizeof(cnt));
    memset(dp, false, sizeof(dp));
    for (int i = 0; i < MX * MX; i++) {
        vals[i][0].clear();
        vals[i][1].clear();
    }
    for (int i = 0; i < n; i++) {
        string s; 
        cin >> s;
        for (int j = 0; j < n; j++) {
            if (s[j] == '#') blocked[i][j] = true;
            else if (s[j] == 'A') sa = mp(i, j);
            else if (s[j] == 'B') sb = mp(i, j);
            else blocked[i][j] = false;
        }
    }
    auto bfs = [&] (int sx, int sy, int x) {
        queue<pi> q;
        q.push(mp(sx, sy));
        dist[sx][sy][x] = 0;
        while (!q.empty()) {
            pi curr = q.front();
            q.pop();
            for (int i = 0; i < 4; i++) {
                pi to = mp(curr.f + dx[i], curr.s + dy[i]); 
                if (valid(to.f, to.s) && !used[to.f][to.s][x]) {
                    if (dist[to.f][to.s][x] > dist[curr.f][curr.s][x] + 1) {
                        dist[to.f][to.s][x] = dist[curr.f][curr.s][x] + 1;
                        q.push(mp(to.f, to.s));
                    }
                }
            }
            used[curr.f][curr.s][x] = true;
        }
    };
    bfs(sa.f, sa.s, 0);
    bfs(sb.f, sb.s, 1);
    if (dist[sb.f][sb.s][0] % 2) {
        cout << "A" << '\n';
        return;
    }
    int goal = (dist[sb.f][sb.s][0] / 2);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            pos[i][j][0] = pos[i][j][1] = mp(-1, -1);
            if (!valid(i, j)) continue;
            if (dist[i][j][0] <= goal) {
                pos[i][j][0] = mp(dist[i][j][0], cnt[dist[i][j][0]][0] + 1);
                cnt[dist[i][j][0]][0]++;
                vals[dist[i][j][0]][0].pb(mp(i, j));
            }
            if (dist[i][j][1] <= goal) {
                pos[i][j][1] = mp(dist[i][j][1], cnt[dist[i][j][1]][1] + 1);
                cnt[dist[i][j][1]][1]++;
                vals[dist[i][j][1]][1].pb(mp(i, j));
            }
        }
    }
    for (auto x : vals[goal][0]) {
        for (auto y : vals[goal][1]) {
            if (blocked[x.f][x.s] || blocked[y.f][y.s]) {
                continue;
            }
            if (x.f == y.f && x.s == y.s) { 
                if (dist[x.f][x.s][1] <= dist[y.f][y.s][0] - 1) {
                    dp[goal % 2][pos[x.f][x.s][0].s][pos[y.f][y.s][1].s] = true;
                }
            }
            else {
                if (dist[x.f][x.s][1] <= dist[y.f][y.s][0]) {
                    dp[goal % 2][pos[x.f][x.s][0].s][pos[y.f][y.s][1].s] = true;
                }
            }
        }
    }
    for (int t = goal - 1; t >= 0; t--) {
        for (auto x : vals[t][0]) {
            for (auto y : vals[t][1]) {
                if (blocked[x.f][x.s] || blocked[y.f][y.s]) {
                    continue;
                }
                bool fok = false;
                for (int k = 0; k < 4; k++) {
                    int fnx = x.f + dx[k], fny = x.s + dy[k];
                    if (!valid(fnx, fny)) continue;
                    if (pos[fnx][fny][0].f != t + 1) {
                        continue;
                    }
                    bool ok = true;
                    for (int k2 = 0; k2 < 4; k2++) {
                        int snx = y.f + dx[k2], sny = y.s + dy[k2];
                        if (!valid(snx, sny)) continue;
                        if (pos[snx][sny][1].f != t + 1) {
                            continue;
                        }
                        // dbg("TRY2", snx, sny);
                        int to = pos[fnx][fny][0].s;
                        int to2 = pos[snx][sny][1].s;
                        ok &= dp[(t % 2) ^ 1][to][to2];
                    }
                    // dbg(k, ok);
                    fok |= ok;
                }
                dp[t % 2][pos[x.f][x.s][0].s][pos[y.f][y.s][1].s] = fok;
            }
        }
    }
    cout << (dp[0][pos[sa.f][sa.s][0].s][pos[sb.f][sb.s][1].s] ? "A" : "B") << '\n';
    return;
}
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T; cin >> T;
    while (T--) {
        solve();
    }
}
