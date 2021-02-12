#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef double db;
typedef string str;

// change ld to db if neccesary
typedef pair<int,int> pi;
typedef pair<ll,ll> pl;
typedef pair<ld,ld> pld;

typedef set<int> si;
typedef set<ll> sl;
typedef set<ld> sld;
typedef set<str> ss;
typedef set<pi> spi;
typedef set<pl> spl;
typedef set<pld> spld;

typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<ld> vld;
typedef vector<str> vs;
typedef vector<pi> vpi;
typedef vector<pl> vpl;
typedef vector<si> vsi;
typedef vector<sl> vsl;
typedef vector<pld> vpld;

#define mp make_pair
#define f first
#define s second
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define rall(x) (x).rbegin(), (x).rend()
#define rsz resize
#define ins insert
#define ft front()
#define bk back()
#define pf push_front
#define pb push_back
#define eb emplace_back
#define lb lower_bound
#define ub upper_bound

#define forr(i,a,b) for (int i = (a); i < (b); i++)
#define ford(i,a,b) for (int i = (a)-1; i >= (b); i--)
#define trav(a,x) for (auto& a: x)

template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; } 
int pct(int x) { return __builtin_popcount(x); } 
int bits(int x) { return 31-__builtin_clz(x); } // floor(log2(x)) 
int cdiv(int a, int b) { return a/b+!(a<0||a%b == 0); } // division of a by b rounded up, assumes b > 0 
int fstTrue(function<bool(int)> f, int lo, int hi) {
	hi ++; assert(lo <= hi); // assuming f is increasing
	while (lo < hi) { // find first index such that f is true 
		int mid = (lo+hi)/2; 
		f(mid) ? hi = mid : lo = mid+1; 
	} 
	return lo;
}

const int INF = 0x3f3f3f3f;
const int NINF = 0xc0c0c0c0;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll NINFLL = 0xc0c0c0c0c0c0c0c0;
const ll MOD = 1e9+7;
const int dx[8] = {1, 0, -1, 0, 1, 1, -1, -1}, dy[8] = {0, 1, 0, -1, -1, 1, -1, 1};
int gcd(int a,int b){return b?gcd(b,a%b):a;}
ll binpow(ll a,ll b){ll res=1;while(b){if(b&1)res=(res*a)%MOD;a=(a*a)%MOD;b>>=1;}return res;}
ll modInv(ll a){return binpow(a, MOD-2);}
bool sortcol(const vl& v1, const vl& v2) {return v1[1] < v2[1];}
bool sortpair(const pi& p1, const pi& p2) {return p1.f < p2.f;}

mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<long long unsigned> distribution(0,10);

void __print(int x) {cerr << x;}
void __print(long x) {cerr << x;}
void __print(long long x) {cerr << x;}
void __print(unsigned x) {cerr << x;}
void __print(unsigned long x) {cerr << x;}
void __print(unsigned long long x) {cerr << x;}
void __print(float x) {cerr << x;}
void __print(double x) {cerr << x;}
void __print(long double x) {cerr << x;}
void __print(char x) {cerr << '\'' << x << '\'';}
void __print(const char *x) {cerr << '\"' << x << '\"';}
void __print(const string &x) {cerr << '\"' << x << '\"';}
void __print(bool x) {cerr << (x ? "true" : "false");}

template<typename T, typename V>
void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}';}
template<typename T>
void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? "," : ""), __print(i); cerr << "}";}
void _print() {cerr << "]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}
#ifndef ONLINE_JUDGE
#define dbg(x...) cerr << "[" << #x << "] = ["; _print(x)
#else
#define dbg(x...)
#endif

const int mxN = 1e6+5;
int q = 1, n, a, b, in[mxN], out[mxN], cnt = 0;
vi adj[mxN];
ld ans[mxN];

template < class T, int SZ > struct LazySeg {
  T tree[4 * SZ], lazy[4 * SZ];
  T merge(T nx, T ny) {
    return nx + ny;
  }
  void build(int v, int l, int r) {
	  tree[v] = 1.0;
	  int m = (l + r) / 2;
	  build(2 * v + 1, l, m);
	  build(2 * v + 2, m + 1, r);
	}
  void prop(int v, int l, int r) {
    if (lazy[v] != 0) {
      tree[v] *= lazy[v];
      if (l != r) {
        lazy[2 * v + 1] *= lazy[v];
        lazy[2 * v + 2] *= lazy[v];
      }
      lazy[v] = 0;
    }
  }
  void update(int v, int l, int r, int ql, int qr, int x) {
    prop(v, l, r);
    if (r < ql || l > qr) {
      return;
    }
    if (l >= ql && r <= qr) {
      tree[v] *= x;
      if (l != r) {
        lazy[2 * v + 1] *= x;
        lazy[2 * v + 2] *= x;
      }
      return;
    }
    int m = (l + r) / 2;
    update(2 * v + 1, l, m, ql, qr, x);
    update(2 * v + 2, m + 1, r, ql, qr, x);
    tree[v] = merge(tree[2 * v + 1], tree[2 * v + 2]);
  }

  T query(int v, int l, int r, int ql, int qr) {
    prop(v, l, r);
    if (l > qr || r < ql) {
      return 0;
    }
    if (l >= ql && r <= qr) {
      return tree[v];
    } else {
      int m = (l + r) / 2;
      T na = query(2 * v + 1, l, m, ql, qr);
      T nb = query(2 * v + 2, m + 1, r, ql, qr);
      return merge(na, nb);
    }
  }
};
LazySeg<ld, (int)4e6> st;

void dfs2(int v, int p = -1) {
	if (p != -1) {
		st.update(0,0,n-1,in[v],out[v]-1,adj[p].size());
		if (in[v] != 0) st.update(0,0,n-1,0,in[v]-1,(ld)1/(ld)adj[v].size());
		if (out[v] != n) st.update(0,0,n-1,out[v],n-1,(ld)1/(ld)adj[v].size());
	}
	ans[v] = st.query(0,0,n-1,0,n-1);
	trav(i,adj[v]) {
		if (i != p) {
			dfs2(i,v);
		}
	}
}
void dfs(int v, int p = -1, ld val = 1) {
	val *= (ld)1/(ld)(adj[v].size()+1);
	st.update(0,0,n-1,v,v,val);
	if (!adj[v].empty()) val *= (ld)(adj[v].size()+1)/(ld)adj[v].size();
	trav(i,adj[v]) {
		if (i != p) {
			dfs(i,v,val);
		}
	}
}
void euler(int v, int p=-1) {
  in[v] = cnt++;  
  for (int to : adj[v]) {
    if (to != p) euler(to, v);
  }  
  out[v] = cnt;
}
void solve() {
	cin >> n;
	forr(i,0,n-1) {
		cin >> a >> b; a--; b--;
		adj[a].pb(b);
		adj[b].pb(a);
	}
	euler(0);
	forr(i,0,n) cout << in[i] << " \n"[i==n-1];
	forr(i,0,n) cout << out[i] << " \n"[i==n-1];
	// update(0,0,n-1,0,n-1,1);
	st.build(0,0,n-1);
	dfs(0);
	dfs2(0);

	// cout << setprecision(12) << fixed;
	// forr(i,0,n) cout << ans[i] << " ";
	// cout << "\n";
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	// freopen(".in", "r", stdin);
	// freopen(".out", "w", stdout);

	// cin >> q;
	while(q--) {
		solve();
	}
}
