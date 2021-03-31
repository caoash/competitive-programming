#include <bits/stdc++.h> 
#include <cassert>
#include <cstring>
// #include "gralib.hpp"
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

int n, k, m;
int _n, _k, _m, _x = 0, _y = -1;

int nastepna(){
    _y = 1 + (rand() % k);
    return _y;
}

void zwieksz() {
    if (_y == -1) {
        assert("NO NUM GEND");
        return;
    }
    if (_x % _y == 0) {
        _x += _y;
    } else {
        assert("NOT DIVISIBLE");
        return;
    }
}

void koniec() {
    assert(_x == _n);
    cout << "CONGRATS YOU WIN\n";
}

int dajN() {
    return _n;
}

int dajK() {
    return _k;
}

int dajM() {
    return _m;
}

const int MX = 250005;
const double EPS = 1e-7;

double dp[MX];
vector<int> take[MX];

void Solve() {
    n = dajN();
    k = dajK();
    m = dajM();
    dbg(n, k, m);
    dp[n] = 0;
    FORD(i, n) {
        double best = 1e9;        
        vector<int> fac;
        F0R(j, 1, k + 1) {
            if (i % j == 0 && i + j <= n) {
                fac.push_back(j);
            }
        }
        sort(fac.begin(), fac.end(), [&] (int a, int b) {
            return (dp[i + b] - dp[i + a]) >= EPS;
        });
        vector<double> psum(fac.size());
        FOR(j, fac.size()) {
            if (j > 0) psum[j] += psum[j - 1];
            psum[j] += (dp[i + fac[j]]);
        }
        auto f = [&] (int mid) {
            double p = ((double) (mid + 1) / (double) k);
            double avg = psum[mid] / (double) (mid + 1);
            return avg + (double) ((double) 1 / p) - 1;
        };
        int lo = 0, hi = fac.size() - 1;
        int ans = -1;
        // double best = 1e9;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            if (f(mid) < best) {
                best = f(mid);
                ans = mid;
            }
            if (f(mid) - f(mid + 1) >= EPS) {
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        /*
        FOR(j, fac.size()) {
            if (f(j) < best) {
                best = f(j);
                ans = j;
            }
        }
        */
        FOR(j, ans + 1) {
            take[i].push_back(fac[j]);
        }
        dp[i] = best;
        dbg(i, best, take[i], psum[ans], ans);
    }
    FOR(tt, 100) {
        _x = 0, _y = -1;
        int pt = 0;
        int moves = 0;
        while (pt < n) {
            int rng = nastepna();
            // dbg(rng);
            ++moves;
            // dbg(pt, take[pt], rng);
            if (pt % rng == 0 && pt + rng <= n) {
                int lo = 0, hi = take[pt].size() - 1;
                bool good = false;
                while (lo <= hi) {
                    int mid = (lo + hi) / 2;
                    if (take[pt][mid] == rng) {
                        good = true;
                        break;
                    } else if (dp[pt + rng] - dp[pt + take[pt][mid]] >= EPS) {
                        lo = mid + 1; 
                    } else {
                        hi = mid - 1;
                    }
                }
                // dbg(pt, rng, take[pt], good);
                if (good) {
                    dbg(pt, moves, rng, dp[pt + rng]);
                    zwieksz();    
                    pt += rng;
                    // ++moves;
                }
            }
            // dbg(pt);
        }
        koniec();
        dbg(moves);
        assert(moves <= m);
    }
    // dbg(moves);
}
 
int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);    
    cin >> _n >> _k >> _m;
    Solve();
}

/*
 * if you take some prefix the EV can be calculated as
 * E = p * avg + (1 - p) * (E + 1)
 * E = p * avg + E + 1 - pE - p
 * pE = p * avg + 1 - p
 * E = avg + (1 / p) - 1
 *
 *
 *
 *
 *
 */
