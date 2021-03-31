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

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

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

mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());

ll MOD = 1000696969;
ll MOD2 = (int) (1e9 + 9);

const int BASE = 69;

int occ[26];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);    
    int n; cin >> n;
    vector<string> strs(n);
    FOR(i, n) cin >> strs[i];
    ll ans = 0;
    vector<pair<ll, ll>> nums[26];
    FOR(i, n) {
        string c = strs[i];
        memset(occ, 0, sizeof(occ));
        FOR(j, c.size()) occ[c[j] - 'a']++;
        ll hsh = 0, bas = 1;
        ll hsh2 = 0, bas2 = 1;
        FOR(k, 26) {
            if (occ[k]) {
                pair<ll, ll> dude = make_pair(hsh, hsh2);
                nums[k].push_back(dude);
            }
        }
        FORD(j, c.size()) {
            hsh += (bas * ((c[j] - 'a') + 1));
            hsh2 += (bas2 * ((c[j] - 'a') + 1));
            if (hsh >= MOD) hsh -= MOD;
            if (hsh2 >= MOD2) hsh2 -= MOD2;
            bas *= BASE;
            bas %= MOD;
            bas2 *= BASE;
            bas2 %= MOD2;
            occ[c[j] - 'a']--;
            FOR(k, 26) {
                if (occ[k]) {
                    pair<ll, ll> dude = make_pair(hsh, hsh2);
                    nums[k].push_back(dude);
                }
            }
        }
    }
    FOR(k, 26) sort(nums[k].begin(), nums[k].end());
    FOR(i, n) {
        string c = strs[i];
        ll hsh = 0, bas = 1;
        ll hsh2 = 0, bas2 = 1;
        F0RD(j, 1, c.size()) {
            hsh += (bas * ((c[j] - 'a') + 1));
            if (hsh >= MOD) hsh -= MOD;
            hsh2 += (bas2 * ((c[j] - 'a') + 1));
            if (hsh2 >= MOD2) hsh2 -= MOD2;
            bas *= BASE;
            bas %= MOD;
            bas2 *= BASE;
            bas2 %= MOD2;
        }
        vector<pair<ll, ll>> &cur = nums[c[0] - 'a'];
        int lo = lower_bound(cur.begin(), cur.end(), make_pair(hsh, hsh2)) - cur.begin();
        int hi = upper_bound(cur.begin(), cur.end(), make_pair(hsh, hsh2)) - cur.begin();
        ans += (hi - lo) - 1;
    }
    cout << ans << '\n';
}

