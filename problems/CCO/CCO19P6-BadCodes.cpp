#include <cmath>
#include <functional>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <set>
#include <map>
#include <list>
#include <time.h>
#include <math.h>
#include <random>
#include <deque>
#include <queue>
#include <cassert>
#include <unordered_map>
#include <unordered_set>
#include <iomanip>
#include <bitset>
#include <sstream>
#include <chrono>
#include <cstring>
using namespace std;
 
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<int, array<int, 3>> T;
 
#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)
#define sz(x) (int)x.size()
 
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
  // #define dbg(x...) pr("[", #x, "] = ["), pc(x);
}

#ifdef mikey 
using namespace output;
#else
using namespace output;
// // #define dbg(x...)
#endif

map<array<int, 3>, int> dist;
set<array<int, 3>> vis;
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);    
    int n, m; cin >> n >> m;
    vector<string> vals(n);
    FOR(i, n) cin >> vals[i];
    // // // dbg(vals);
    dist[{0, 0, 0}] = 0;
    priority_queue<T, vector<T>, greater<T>> pq;
    array<int, 3> init = {0, 0, 0};
    pq.push(make_pair(0, init));
    auto rem = [&] (pi a, pi b) {
        if (a.S > b.S) {
            return make_pair(a.F, a.S - b.S);
        } else {
            return make_pair(b.F, b.S - a.S);
        }
    };
    /*
    auto rrem = [&] (string &a, string &b) {
        if (a.size() > b.size()) {
            return a.substr(0, a.size() - b.size());
        } else {
            return b.substr(0, b.size() - a.size());
        }
    };
    */
    auto prop = [&] (pair<int, array<int, 3>> &state) {
        if (state.S[1] > m) return;
        if (!vis.count(state.S)) {
            if (!dist.count(state.S)) {
                dist[state.S] = state.F;
                pq.push(make_pair(state.F, state.S));
            } else if (dist[state.S] > state.F) {
                dist[state.S] = state.F;
                pq.push(make_pair(state.F, state.S));
            }
        }
    };
    int ans = 1e9;
    while (!pq.empty()) {
        auto curr = pq.top();
        // dbg(curr);
        pq.pop();
        if (vis.count(curr.S)) continue;
        FOR(i, n) {
            /*
            if (curr.S.S + vals[i].size() <= m) {
                T fir = make_pair(curr.F, 
                        make_pair(curr.S.F, curr.S.S + vals[i].size()));
                prop(fir);
            }
            */
            bool good = true;
            FOR(j, min(sz(vals[i]), curr.S[1])) {
                if (vals[i][j] !=
                        vals[curr.S[0]][sz(vals[curr.S[0]]) - curr.S[1] + j]) {
                    good = false;
                }
            }
            if (good) {
                pi ns = rem(make_pair(curr.S[0], curr.S[1]), 
                        make_pair(i, sz(vals[i])));
                array<int, 3> sta;
                sta[2] = 0;
                sta[0] = ns.F, sta[1] = ns.S;
                sta[2] |= curr.S[2];
                if (ns.S > 0 && curr.S[1] > 0) {
                    sta[2] |= 1;
                }
                int ndist = curr.F + min(sz(vals[i]), curr.S[1]);
                T sec = make_pair(ndist, sta);
                // dbg(curr, sta, vals[i]);
                prop(sec);
            }
        }
        if (curr.S[2] == 1 && curr.S[1] == 0) {
            // dbg(curr);
            ans = min(ans, curr.F);
        }
        vis.insert(curr.S);
    }
    // // // dbg(dist);
    /*
    FOR(i, n) {
        F0R(j, i + 1, n) {
            bool good = true;
            FOR(k, min(sz(vals[i]), sz(vals[j]))) {
                if (vals[i][sz(vals[i]) - k - 1] != vals[j][sz(vals[j]) - k - 1]) {
                    good = false;
                }
            }
            if (!good) continue;
            string res = rrem(vals[i], vals[j]);
            // // // dbg(vals[i], vals[j], res);
            FOR(k, n) {
                if (vals[k].size() >= res.size()) {
                    string s = vals[k].substr(vals[k].size() - res.size(), res.size());
                    if (s == res && dist.count(make_pair(k, sz(res)))) {
                        int cur = min(ans, dist[make_pair(k, sz(res))] + 
                                min(sz(vals[i]), sz(vals[j])) + sz(res));
                        ans = min(ans, cur);
                        // // // dbg(k, sz(res), ans);
                    }
                }
            }
        }
    }
    */
    cout << (ans == 1e9 ? -1 : ans)  << '\n';
}
