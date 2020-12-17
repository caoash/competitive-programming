#include <bits/stdc++.h> 
using namespace std;

using ll = long long;

using vi = vector<int>;
using vl = vector<ll>;
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define lb lower_bound
#define ub upper_bound

using pi = pair<int,int>;
using T = pair<int, pi>;
#define f first
#define s second
#define mp make_pair

const int MX = 200005;
const int MOD = (int) (1e9 + 7);
const ll INF = (ll) 1e18;

namespace output {
  void pr(int x) {
    cout << x;
  }
  void pr(long x) {
    cout << x;
  }
  void pr(ll x) {
    cout << x;
  }
  void pr(unsigned x) {
    cout << x;
  }
  void pr(unsigned long x) {
    cout << x;
  }
  void pr(unsigned long long x) {
    cout << x;
  }
  void pr(float x) {
    cout << x;
  }
  void pr(double x) {
    cout << x;
  }
  void pr(long double x) {
    cout << x;
  }
  void pr(char x) {
    cout << x;
  }
  void pr(const char * x) {
    cout << x;
  }
  void pr(const string & x) {
    cout << x;
  }
  void pr(bool x) {
    pr(x ? "true" : "false");
  }

  template < class T1, class T2 > void pr(const pair < T1, T2 > & x);
  template < class T > void pr(const T & x);

  template < class T, class...Ts > void pr(const T & t,
    const Ts & ...ts) {
    pr(t);
    pr(ts...);
  }
  template < class T1, class T2 > void pr(const pair < T1, T2 > & x) {
    pr("{", x.f, ", ", x.s, "}");
  }
  template < class T > void pr(const T & x) {
    pr("{"); // const iterator needed for vector<bool>
    bool fst = 1;
    for (const auto & a: x) pr(!fst ? ", " : "", a), fst = 0;
    pr("}");
  }

  void ps() {
    pr("\n");
  } // print w/ spaces
  template < class T, class...Ts > void ps(const T & t,
    const Ts & ...ts) {
    pr(t);
    if (sizeof...(ts)) pr(" ");
    ps(ts...);
  }

  void pc() {
    cout << "]" << endl;
  } // debug w/ commas
  template < class T, class...Ts > void pc(const T & t,
    const Ts & ...ts) {
    pr(t);
    if (sizeof...(ts)) pr(", ");
    pc(ts...);
  }
  #define dbg(x...) pr("[", #x, "] = ["), pc(x);
}

#ifdef mikey 
using namespace output;
#else
using namespace output;
#define dbg(x...)
#endif

int H, W, K;
bool blocked[805][805];
bool can[805][805];
bool vis[805][805];
int dist[805][805];
int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};

bool valid(int x, int y) {
    return x >= 0 && y >= 0 && x < H && y < W && !vis[x][y];
}

void bfs(int x, int y) {
    queue<pi> q;
    q.push(mp(x, y));
    memset(dist, 0x3f3f3f, sizeof(dist));
    dist[x][y] = 0;
    while (!q.empty()) {
        pi curr = q.front();
        q.pop();
        if (dist[curr.f][curr.s] <= K) can[curr.f][curr.s] = true;
        for (int k = 0; k < 4; k++) {
            int nx = curr.f + dx[k], ny = curr.s + dy[k];
            if (valid(nx, ny) && !blocked[nx][ny]) {
                if (dist[nx][ny] > dist[curr.f][curr.s] + 1) {
                    dist[nx][ny] = dist[curr.f][curr.s] + 1;
                    q.push(mp(nx, ny));
                }
            }
        }
        vis[curr.f][curr.s] = true;
    }
}

int main(){
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> H >> W >> K;
    pi st = mp(-1, -1);
    for (int i = 0; i < H; i++) {
        string s; cin >> s;
        for (int j = 0; j < W; j++) {
            blocked[i][j] = (s[j] == '#');
            if (s[j] == 'S') st = mp(i, j);
        }
    }
    bfs(st.f, st.s);
    int ans = INT_MAX;
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (can[i][j]) {
                int best = min({i, j, H - i - 1, W - j - 1});
                ans = min(ans, 1 + (int)ceil((double)best / (double)K));
            }
        }
    }
    cout << ans << '\n';
}

