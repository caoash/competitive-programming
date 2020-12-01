/*
 * Apply a greedy algorithm where you add the two numbers together, then if there's two consecutive update a[i + 2] and subtract a[i] and a[i + 1], then solve for i + 2.
 * If a[i] > 1, then a[i] -= 2 and a[i + 1]++ and a[i - 2]++. Then, solve for i + 1.
 * Otherwise, solve for i - 1.
 *
 * The key to making this run in time is going backwards (going forwards gets 6/10 and TLE on the rest). 
 *
 * Basic proof of why:
 * Whenever you have to backtrack when going backwards, it's because either cnt[i] > 1 or cnt[i] = 1 and cnt[i + 1] = 1.
 *
 * Case 1: cnt[i] = 1 and cnt[i + 1] = 1,
 *  In this case, notice the total number of 1s decreases by 1, since they merge together. That means, you only need to backtrack at most # 1's times.
 * Case 2: cnt[i] > 1
 *  In this case, we can assume that cnt[i + 1] = 0, since if cnt[i + 1] = 1 then that falls under the first case. Also notice that cnt[i] <= 1 for j > i, since we've already solved those positiions.
 *  If cnt[i + 1] = 0, then when we do cnt[i] -= 2 and cnt[i + 1]++ and cnt[i - 2]++, backtracking to i + 1 won't lead to another cnt[i] > 1 event.
 *  This case happens at most once per position and never happens when backtracking.
 *
 * However, when you go forwards, it's not as nice. The main reason is that if cnt[i] > 1, then we have to backtrack to cnt[i - 2], which could trigger even more cnt[i] > 1 events without decreasing
 * the number of 1's, which leads to TLE.
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

const int MX = 1000005;
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

#ifdef LOCAL
using namespace output;
#endif

int cnt[MX];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int len = 0;
    for (int i = 0; i < 2; i++) {
        int n; cin >> n; 
        len = max(len, n);
        for (int j = 0; j < n; j++) {
            int x; cin >> x;
            cnt[j] += x;
        }
    }
    for (int i = MX - 1; i >= 0; i--) {
        if (cnt[i] == 1 && cnt[i + 1] == 1) {
            cnt[i]--;
            cnt[i + 1]--;
            cnt[i + 2]++;
        }
        else if (i > 0 && cnt[i] == 1 && cnt[i - 1] == 1) {
            cnt[i]--;
            cnt[i - 1]--;
            cnt[i + 1]++;
        }
        else {
            if (i == 0) {
                if (cnt[i] > 1) {
                    cnt[i] -= 2;
                    cnt[1]++;
                }
            }
            else if (i == 1) {
                if (cnt[i] > 1) {
                    cnt[i] -= 2;
                    cnt[0]++;
                    cnt[2]++;
                    i -= 2;
                }
            }
            else {
                if (cnt[i] > 1) {
                    cnt[i] -= 2;
                    cnt[i - 2]++;
                    cnt[i + 1]++;
                    i -= 3;
                }
            }
        }
    }
    int mx = 0;
    for (int i = 0; i < MX; i++) {
        if (cnt[i]) mx = i;
    }
    cout << mx + 1 << " ";
    for (int i = 0; i <= mx; i++) {
        cout << cnt[i] << " ";
    }
    cout << '\n';
}
