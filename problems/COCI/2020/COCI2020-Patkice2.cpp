#include <bits/stdc++.h> 
using namespace std;

typedef long long ll;

#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)

#define F first
#define S second

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
    pr("{", x.F, ", ", x.S, "}");
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

const int MX = 2005;

int n, m;

int mp(int x, int y) {
    return 2000 * x + y;
}

vector<pair<int, int>> adj[MX * MX];
bool vis[MX * MX];
int dist[MX * MX];
int pre[MX * MX];
char grid[MX][MX];

int dx[] = {0, -1, 0, 1}, dy[] = {1, 0, -1, 0};

void add(int x, int y, int dir) {
    int pos = mp(x, y);
    FOR(i, 4) {
        int nx = x + dx[i], ny = y + dy[i];
        if (nx >= 0 && ny >= 0 && nx < n && ny < m) {
            adj[pos].push_back({mp(nx, ny), ((i == dir || dir == -1) ? 0 : 1)});
        }
    }
}

int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    int st = -1, en = -1;
    FOR(i, n) {
        string s; cin >> s;
        FOR(j, m) {
            if (s[j] == '>') {
                add(i, j, 0); 
            } else if (s[j] == '<') {
                add(i, j, 2);
            } else if (s[j] == '^') {
                add(i, j, 1);
            } else if (s[j] == 'v') {
                add(i, j, 3);
            } else if (s[j] == '.') {
                add(i, j, -2);
            } else if (s[j] == 'o') {
                st = mp(i, j);
                add(i, j, -1);
            } else {
                en = mp(i, j);
            }
            dist[mp(i, j)] = 1e9;
            grid[i][j] = s[j];
        }
    }
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, st});
    dist[st] = 0;
    while (!pq.empty()) {
        pair<int, int> fr = pq.top();
        pq.pop();
        int curr = fr.S;
        if (vis[curr]) continue;
        for (auto to : adj[curr]) {
            if (!vis[to.F]) {
                if (dist[curr] + to.S < dist[to.F]) {
                    dist[to.F] = dist[curr] + to.S;
                    pq.push({dist[to.F], to.F});
                    pre[to.F] = curr;
                }
            }
        }
        vis[curr] = true;
    }
    int at = en;
    string dirs = ">^<v";
    while (pre[at] != st) {
        int cx = at / 2000, cy = at % 2000;
        int pcx = (pre[at] / 2000), pcy = (pre[at] % 2000);
        FOR(i, 4) {
            int nx = cx + dx[i], ny = cy + dy[i];
            if (nx == pcx && ny == pcy) {
                grid[pcx][pcy] = dirs[(i + 2) % 4]; 
            }
        }
        at = pre[at];
    }
    cout << dist[en] << '\n';
    FOR(i, n) {
        FOR(j, m) {
            cout << grid[i][j];
        }
        cout << '\n';
    }
}

