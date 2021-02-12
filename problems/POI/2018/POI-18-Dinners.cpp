#include <bits/stdc++.h> 
using namespace std;

typedef long long ll;
typedef pair<ll, int> pi;

#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)

#define F first
#define S second

const int MX = 100005;

namespace IO {
    const int BUFFER_SIZE = 1 << 15;

    char input_buffer[BUFFER_SIZE];
    int input_pos = 0, input_len = 0;

    char output_buffer[BUFFER_SIZE];
    int output_pos = 0;

    char number_buffer[100];
    uint8_t lookup[100];

    void _update_input_buffer() {
        input_len = fread(input_buffer, sizeof(char), BUFFER_SIZE, stdin);
        input_pos = 0;

        if (input_len == 0)
            input_buffer[0] = EOF;
    }

    inline char next_char(bool advance = true) {
        if (input_pos >= input_len)
            _update_input_buffer();

        return input_buffer[advance ? input_pos++ : input_pos];
    }

    template<typename T>
    inline void read_int(T &number) {
        bool negative = false;
        number = 0;

        while (!isdigit(next_char(false)))
            if (next_char() == '-')
                negative = true;

        do {
            number = 10 * number + (next_char() - '0');
        } while (isdigit(next_char(false)));

        if (negative)
            number = -number;
    }

    template<typename T, typename... Args>
    inline void read_int(T &number, Args &... args) {
        read_int(number);
        read_int(args...);
    }

    void _flush_output() {
        fwrite(output_buffer, sizeof(char), output_pos, stdout);
        output_pos = 0;
    }

    inline void write_char(char c) {
        if (output_pos == BUFFER_SIZE)
            _flush_output();

        output_buffer[output_pos++] = c;
    }

    template<typename T>
    inline void write_int(T number, char after = '\0') {
        if (number < 0) {
            write_char('-');
            number = -number;
        }

        int length = 0;

        while (number >= 10) {
            uint8_t lookup_value = lookup[number % 100];
            number /= 100;
            number_buffer[length++] = (lookup_value & 15) + '0';
            number_buffer[length++] = (lookup_value >> 4) + '0';
        }

        if (number != 0 || length == 0)
            write_char(number + '0');

        for (int i = length - 1; i >= 0; i--)
            write_char(number_buffer[i]);

        if (after)
            write_char(after);
    }

    void init() {
        // Make sure _flush_output() is called at the end of the program.
        bool exit_success = atexit(_flush_output) == 0;
        assert(exit_success);

        for (int i = 0; i < 100; i++)
            lookup[i] = (i / 10 << 4) + i % 10;
    }
}


template < int SZ > struct LCA {
    int depth[SZ];
    ll far[SZ];
    int p[SZ][17];
    vector<pi> adj[SZ];
    void addEdge(int u, int v, int w) {
      adj[u].push_back({v, w});
      adj[v].push_back({u, w});
    }
    void dfs(int v, int par) {
      for (pi e : adj[v]) {
        int to = e.F;
        if (to != par) {
          p[to][0] = v;
          depth[to] = depth[v] + 1;
          far[to] = far[v] + e.S;
          dfs(to, v);
        }
      }
    }
    void precomp(int root) {
      for (int i = 0; i < SZ; i++) {
        for (int j = 0; j < 17; j++) {
          p[i][j] = -1;
        }
      }
      p[root][0] = 0;
      dfs(root, -1);
      for (int j = 1; j < 17; j++) {
        for (int i = 0; i < SZ; i++) {
          if (p[i][j - 1] == -1) {
            p[i][j] = -1;
          } else {
            p[i][j] = p[p[i][j - 1]][j - 1];
          }
        }
      }
    }
    int query(int a, int b) {
      if (depth[a] > depth[b]) {
        swap(a, b);
      }
      int lift = depth[b] - depth[a];
      for (int j = 16; j >= 0; j--) {
        if (lift & (1 << j)) {
          b = p[b][j];
        }
      }
      for (int j = 16; j >= 0; j--) {
        if (p[a][j] != p[b][j]) {
          a = p[a][j];
          b = p[b][j];
        }
      }
      return (a == b) ? a : p[a][0];
    }
    ll dist(int a, int b) {
      return far[a] + far[b] - (2 * far[query(a, b)]);  
    }
};

ll dat[MX];
vector<pair<pair<int, int>, int>> qrs[MX];
vector<int> nods[MX];
vector<pi> adj[MX];
ll dist[MX];
ll qd[MX][17];
ll ret[MX];
LCA<MX> anc;
int n, r; 

int main() {
    IO::init();
    IO::read_int(n);
    IO::read_int(r);
    FOR(i, n) {
        IO::read_int(dat[i]);
        dat[i]--;
        nods[dat[i]].push_back(i);
    }
    FOR(i, n - 1) {
        int u, v, w; 
        IO::read_int(u);
        IO::read_int(v);
        IO::read_int(w);
        u--, v--;
        anc.addEdge(u, v, w);
        adj[u].push_back({v, w}), adj[v].push_back({u, w});
    }
    anc.precomp(0);
    int q; 
    IO::read_int(q);
    FOR(i, q) {
        int a, b, c;
        IO::read_int(a);
        IO::read_int(b);
        IO::read_int(c);
        a--, b--, c--;
        qrs[c].push_back({{a, b}, i});
    }
    auto SolveSmall = [&] (int u, int v, int c) {
        ll ans = 1e18;
        for (auto x : nods[c]) {
            ans = min(ans, anc.dist(u, x) + anc.dist(v, x)); 
        }
        return (ans == 1e18 ? -1 : ans);
    };

    auto PrecompBig = [&] (int c) {
        FOR(i, n) dist[i] = 1e18;
        queue<int> pq;
        for (auto x : nods[c]) {
            dist[x] = 0, pq.push(x);
        }
        while (!pq.empty()) {
            auto curr = pq.front();
            pq.pop();
            for (auto to : adj[curr]) {
                if (dist[to.F] > dist[curr] + to.S) {
                    dist[to.F] = dist[curr] + to.S;
                    pq.push(to.F);
                }
            }
        }
        for (int i = 0; i < n; i++) {
            qd[i][0] = dist[i];
            for (int j = 1; j < 17; j++) {
                qd[i][j] = 1e18;
            }
        }
        for (int j = 1; j < 17; j++) {
            for (int i = 0; i < n; i++) {
              if (anc.p[i][j - 1] == -1) {
                  qd[i][j] = 1e18;
              } else {
                  qd[i][j] = min(qd[i][j - 1], qd[anc.p[i][j - 1]][j - 1]);
              }
            }
        }
    };

    auto SolveBig = [&] (int u, int v) {
        if (anc.depth[u] > anc.depth[v]) {
          swap(u, v);
        }
        ll res = 1e18;
        int lift = anc.depth[v] - anc.depth[u];
        for (int j = 16; j >= 0; j--) {
          if (lift & (1 << j)) {
             res = min(res, qd[v][j]);
             v = anc.p[v][j];
          }
        }
        for (int j = 16; j >= 0; j--) {
          if (anc.p[u][j] != anc.p[v][j]) {
              res = min(res, qd[u][j]);
              res = min(res, qd[v][j]);
              u = anc.p[u][j];
              v = anc.p[v][j];
          }
        }
        res = min(res, qd[u][0]);
        res = min(res, qd[v][0]);
        if (u == v) {
            return (res == 1e18 ? -1 : res);
        } else {
            res = min(res, qd[anc.p[u][0]][0]);
            return (res == 1e18 ? -1 : res);
        }
    };
    FOR(c, r) {
        if (nods[c].size() <= 500) {
            for (auto cq : qrs[c]) {
                ll res = SolveSmall(cq.F.F, cq.F.S, c);
                ret[cq.S] = res;
            }
        } else {
            PrecompBig(c); 
            for (auto cq : qrs[c]) {
                ll res = SolveBig(cq.F.F, cq.F.S);
                if (res != -1) res = (2 * res + anc.dist(cq.F.F, cq.F.S));
                ret[cq.S] = res;
            }
        }
    }
    FOR(i, q) IO::write_int(ret[i], '\n'); 
}

