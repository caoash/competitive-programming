#include <bits/stdc++.h> 
using namespace std;

using ll = long long;

using vi = vector<int>;
using vl = vector<ll>;
#define pb push_back
#define rsz resize
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define lb lower_bound
#define ub upper_bound

using pi = pair<int,int>;
#define f first
#define s second
#define mp make_pair

const int MX = 100005;
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

set<int> htree[4 * MX], vtree[4 * MX];

int A, B;

void update(int v, int l, int r, int ul, int ur, int x, int t) {
    if (ul > r || ur < l) {
        return;
    } else if(l >= ul && r <= ur) {
        if (!t) {
            htree[v].insert(x);
        } else {
            vtree[v].insert(x);
        }
        return;
    } else {
        int m = (l + r) / 2;
        update(2 * v + 1, l, m, ul, ur, x, t);
        update(2 * v + 2, m + 1, r, ul, ur, x, t);
        return;
    }
}

pi query(int v, int l, int r, int qi, int t, int x) {
    pi curr = mp(-1, INT_MAX);
    if (!t) {
        auto it = htree[v].lb(x);
        if (it != htree[v].end()) curr.s = *it;
        if (it != htree[v].begin()) curr.f = *(--it);
    } else {
        auto it = vtree[v].lb(x);
        if (it != vtree[v].end()) curr.s = *it;
        if (it != vtree[v].begin()) curr.f = *(--it);
    }
    if (l == r) {
        return curr;
    } else {
        int m = (l + r) / 2;
        pi nxt;
        if (m >= qi) {
            nxt = query(2 * v + 1, l, m, qi, t, x); 
        } else {
            nxt = query(2 * v + 2, m + 1, r, qi, t, x);
        }
        curr.f = max(curr.f, nxt.f);
        curr.s = min(curr.s, nxt.s);
        return curr;
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> A >> B;

    update(0, 0, A, 0, A, 0, 0);
    update(0, 0, A, 0, A, B, 0);
    update(0, 0, B, 0, B, 0, 1);
    update(0, 0, B, 0, B, A, 1);

    int n; cin >> n;

    cout << '\n';
    for (int i = 0; i < n; i++) {
        int x, y, d; cin >> x >> y >> d;
        d--;
        array<ll, 4> cans;
        pi fx = query(0, 0, A, x, 0, y);
        pi sx = query(0, 0, B, y, 1, x);
        cans[0] = fx.s, cans[1] = fx.f, cans[2] = sx.s, cans[3] = sx.f;
        // dbg(x, y, d, cans);
        ll area = 0;
        ll area2 = 0;
        if (!d) {
            area = (cans[0] - y) * (cans[2] - cans[3]);
            area2 = (y - cans[1]) * (cans[2] - cans[3]);
            update(0, 0, A, cans[3], cans[2], y, 0);
        }
        else {
            area = (cans[2] - x) * (cans[0] - cans[1]);
            area2 = (x - cans[3]) * (cans[0] - cans[1]);
            update(0, 0, B, cans[1], cans[0], x, 1);
        }
        if (area > area2) swap(area, area2);
        cout << area << " " << area2 << '\n';
    }
}
