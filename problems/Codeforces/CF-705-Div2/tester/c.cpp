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

void Solve() {
    int N, K; cin >> N >> K;
    string s; cin >> s;
    vector<int> cnt(26);
    string alph = "abcdefghijklmnopqrstuvwxyz";
    FOR(i, N) cnt[s[i] - 'a']++;
    bool good = true;
    FOR(i, 26) {
        if (cnt[i] % K != 0) {
            good = false;
        }
    }
    if (good) {
        cout << s << '\n';
        return;
    }
    FORD(i, N) {
        cnt[s[i] - 'a']--;
        F0R(j, s[i] - 'a' + 1, 26) {
            cnt[j]++;
            vector<int> need(26);
            int tot = 0;
            FOR(k, 26) {
                need[k] += ((K - (cnt[k] % K)) % K);
                tot += need[k];
            }
            if (tot <= N - i - 1) {
                int rem = (N - i - 1) - tot;
                if (rem % K == 0) {
                    FOR(k, rem) need[0]++;
                    string res = "";
                    FOR(k, i) res += s[k];
                    res += alph[j];
                    FOR(k, 26) {
                        FOR(l, need[k]) {
                            res += alph[k];
                        }
                    }
                    cout << res << '\n';
                    return;
                }
            }
            cnt[j]--;
        }
    }
    cout << -1 << '\n';
    return;
}
 
int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);    
    int T; cin >> T;
    while (T--) {
        Solve();
    }
}

