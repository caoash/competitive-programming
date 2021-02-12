#include <bits/stdc++.h> 
using namespace std;

typedef long long ll;

#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)

#define F first
#define S second

const int MX = 30005;

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

struct Node {
    int adj[2];
    bool leaf = false;
    int p = -1;
    int pch;
    int suf = -1;
    int dp[2];
    Node() {
        memset(dp, -1, sizeof(dp));
        memset(adj, -1, sizeof(adj));
        pch = -1;
    };
};

struct AhoCorasick {
    Node gr[MX]; 
    int col[MX][2];
    int pt;

    AhoCorasick() {
        pt = 1;
        memset(col, 0, sizeof(col));
    }

    void Add(string s) {
        int pos = 0;
        for (char c : s) {
            int g = (c - '0');
            if (gr[pos].adj[g] == -1) {
                gr[pos].adj[g] = pt;
                gr[pt].p = pos, gr[pt].pch = g;
                ++pt;
            }
            pos = gr[pos].adj[g];
        }
        gr[pos].leaf = true;
    }

    int Get(int v) {
        if (gr[v].suf == -1) {
            if (v == 0 || gr[v].p == 0) {
                gr[v].suf = 0;
            } else {
                int res = Go(Get(gr[v].p), gr[v].pch);
                gr[v].suf = res; 
            }
        }
        return gr[v].suf;
    }

    int Go(int v, int g) {
        if (gr[v].dp[g] == -1) {
            if (gr[v].adj[g] != -1) {
                gr[v].dp[g] = gr[v].adj[g];
            } else {
                gr[v].dp[g] = (v == 0 ? 0 : Go(Get(v), g));
            }
        } 
        return gr[v].dp[g];
    }

    bool dfs(int v, int g) {
        if (gr[v].leaf) return false;
        vector<int> to; 
        int e = Go(v, g);
        col[v][g] = 1;
        bool good = false;
        FOR(i, 2) {
            dbg(v, g, e, i);
            if (col[e][i] == 1) good = true;
            else if (col[e][i] != 2) good |= dfs(e, i);
        }
        col[v][g] = 2;
        return good;
    }

    bool HasCycle() {
        bool ans = false;
        FOR(i, pt) {
            if (col[i][0] == 0) {
                bool go = dfs(i, 0);
                if (go) dbg(i, 0);
                ans |= go;
            }
            if (col[i][1] == 0) {
                bool go = dfs(i, 1);
                if (go) dbg(i, 1);
                ans |= go;
            }
        }
        return ans;
    }
};

AhoCorasick ahh;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    FOR(i, n) {
        string s; cin >> s;
        ahh.Add(s);
    }
    bool ans = ahh.HasCycle();
    cout << (ans ? "TAK" : "NIE") << '\n';
}
