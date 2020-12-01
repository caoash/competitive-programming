/*
First, realize the order of songs doesn't matter, so sort it. Also, if you cover some interval of length x, you can extend it to y > x.

The problem reduces to: given N points, place disjoint segments of length X >= K whose sum of lengths is minimized
and covers all points.

Then observe some interval should end at a point, and either start at a point or be length K (and possibly not start at a point). 
This is because for interval of length V > K that doesn't start at a point, you can either make it length K or make it start at a point.

Then dp[i] = minimum sum of lengths that covers all points storing prefix maximums of DP values. 

Then store prefix maximums in the form of dp[i - 1] - (pt(i) - 1) for fast transitions.
	
*/

#pragma GCC target ("sse4")

#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
 
typedef long long ll;
typedef long double ld;
typedef complex<ld> cd;

typedef pair<int, int> pi;
typedef pair<ll,ll> pl;
typedef pair<ld,ld> pd;
typedef pair<int, pi> pii;

typedef vector<int> vi;
typedef vector<ld> vd;
typedef vector<ll> vl;
typedef vector<pi> vpi;
typedef vector<pl> vpl;
typedef vector<cd> vcd;

#define fax(i, a) for (int i = 0; i < (a); i++)
#define f0x(i, a, b) for (int i = (a); i < (b); i++)
#define f0xd(i,a,b) for (int i = (b)-1; i >= (a); i--)
#define faxd(i,a) for (int i = (a)-1; i >= 0; i--)
#define trav(a, x) for (auto& a : x)
#define memeset memset

#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound

#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)
#define rsz resize

template<class T> void ckmin(T &a, T b) { a = min(a, b); }
template<class T> void ckmax(T &a, T b) { a = max(a, b); }

template <class T, int ...Ns> struct BIT {
    T val = 0;
    void upd(T v) { val += v; }
    T query() { return val; }
};
 
template <class T, int N, int... Ns> struct BIT<T, N, Ns...> {
    BIT<T,Ns...> bit[N + 1];
    template<typename... Args> void upd(int pos, Args... args) {
        for (; pos <= N; pos += (pos&-pos)) bit[pos].upd(args...);
    }
    template<typename... Args> T sum(int r, Args... args) {
        T res = 0; for (; r; r -= (r&-r)) res += bit[r].query(args...); 
        return res;
    }
    template<typename... Args> T query(int l, int r, Args... args) {
        return sum(r,args...)-sum(l-1,args...);
    }
};

namespace input {
    template<class T> void re(complex<T>& x);
    template<class T1, class T2> void re(pair<T1,T2>& p);
    template<class T> void re(vector<T>& a);
    template<class T, size_t SZ> void re(array<T,SZ>& a);

    template<class T> void re(T& x) { cin >> x; }
    void re(double& x) { string t; re(t); x = stod(t); }
    void re(ld& x) { string t; re(t); x = stold(t); }
    template<class T, class... Ts> void re(T& t, Ts&... ts) { 
        re(t); re(ts...); 
    }

    template<class T> void re(complex<T>& x) { T a,b; re(a,b); x = cd(a,b); }
    template<class T1, class T2> void re(pair<T1,T2>& p) { re(p.f,p.s); }
    template<class T> void re(vector<T>& a) { fax(i,sz(a)) re(a[i]); }
    template<class T, size_t SZ> void re(array<T,SZ>& a) { fax(i,SZ) re(a[i]); }
}

using namespace input;

namespace output {
    void pr(int x) { cout << x; }
    void pr(long x) { cout << x; }
    void pr(ll x) { cout << x; }
    void pr(unsigned x) { cout << x; }
    void pr(unsigned long x) { cout << x; }
    void pr(unsigned long long x) { cout << x; }
    void pr(float x) { cout << x; }
    void pr(double x) { cout << x; }
    void pr(ld x) { cout << x; }
    void pr(char x) { cout << x; }
    void pr(const char* x) { cout << x; }
    void pr(const string& x) { cout << x; }
    void pr(bool x) { pr(x ? "true" : "false"); }
    
    template<class T1, class T2> void pr(const pair<T1,T2>& x);
    template<class T> void pr(const T& x);
    
    template<class T, class... Ts> void pr(const T& t, const Ts&... ts) { 
        pr(t); pr(ts...); 
    }
    template<class T1, class T2> void pr(const pair<T1,T2>& x) { 
        pr("{",x.f,", ",x.s,"}"); 
    }
    template<class T> void pr(const T& x) { 
        pr("{"); // const iterator needed for vector<bool>
        bool fst = 1; for (const auto& a: x) pr(!fst?", ":"",a), fst = 0; 
        pr("}");
    }
    
    void ps() { pr("\n"); } // print w/ spaces
    template<class T, class... Ts> void ps(const T& t, const Ts&... ts) { 
        pr(t); if (sizeof...(ts)) pr(" "); ps(ts...); 
    }
    
    void pc() { pr("]\n"); } // debug w/ commas
    template<class T, class... Ts> void pc(const T& t, const Ts&... ts) { 
        pr(t); if (sizeof...(ts)) pr(", "); pc(ts...); 
    }
    #define dbg(x...) pr("[",#x,"] = ["), pc(x);
}

using namespace output;

namespace io {
    void setIn(string s) { freopen(s.c_str(),"r",stdin); }
    void setOut(string s) { freopen(s.c_str(),"w",stdout); }
    void setIO(string s = "") {
        ios_base::sync_with_stdio(0); cin.tie(0); // fast I/O
        if (sz(s)) { setIn(s+".in"), setOut(s+".out"); } // for USACO
    }
}

using namespace io;

mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());

const int MOD = 1000000007; // 998244353
const ll INF = 1e18;
const int MX = 300005;
const ld PI = 4*atan((ld)1);

ll dp[MX]; pair<ll, int> pre[MX]; int fr[MX];

int main() {
    setIO(); 
    int n, k, m; re(n, k, m);
    set<pi> a; vi b, q;
    b.pb(0);
    fax(i, m){
    	int x; re(x);
    	b.pb(x), q.pb(x);
    }
    sort(all(b));
    fax(i, sz(b)){
    	a.insert(mp(b[i], i));
    }
    fax(i, m + 1) dp[i] = INF;
	dp[0] = 0;    
	f0x(i, 1, m + 1){
		if(b[i] <= k){
			dp[i] = k;
			fr[i] = -1;
		}
		else{
			auto it = a.lb(mp(b[i] - (k - 1), INT_MIN));
			// dbg(*it);
			--it;
			// dbg(b[i], k, i, (it -> s));
			int pv = (it -> s);
			if(dp[pv] + k < dp[i]){
				dp[i] = dp[pv] + k;
				fr[i] = -1;
			}
			if(pre[pv].f + b[i] < dp[i]){
				dp[i] = pre[pv].f + b[i]; 
				fr[i] = pre[pv].s;
			}
			ckmin(dp[i], pre[(it -> s)].f + b[i]);
		}
		pre[i] = min(pre[i - 1], mp(dp[i - 1] - (b[i] - 1), i));
		// dbg(i, dp[i], pre[i]);
	}
	int cur = m;
	set<pi> segs;
	while(cur > 0){
		// dbg(cur, fr[cur], b[cur]);
		if(fr[cur] == -1){
			if(b[cur] <= k){
				segs.insert(mp(1, k));
				break;
			} 
			else{
				segs.insert(mp(b[cur] - (k - 1), b[cur]));
				auto to = a.lb(mp(b[cur] - (k - 1), INT_MIN));
				--to;
				cur = (to -> s);
			} 
		}
		else{
			segs.insert(mp(b[fr[cur]], b[cur]));
			// dbg(cur, b[fr[cur]], b[cur]);
			cur = fr[cur] - 1;
		}
		// dbg(cur, fr[cur]);
		// cout << endl;
	}
	// dbg(segs);
	stack<pi> mrg;	
	set<pi> nsegs;
	trav(curr, segs){
		if(mrg.empty()){
			mrg.push(curr);
		}
		else{
			if(mrg.top().s < curr.f){
				mrg.push(curr);
			}
			else{
				pi nxt = mp(mrg.top().f, curr.s);
				mrg.pop();
				mrg.push(nxt);
			}
		}
	}
	ps(dp[m]);
	while(!mrg.empty()) {
		nsegs.insert(mrg.top());
		mrg.pop();
	}
	// dbg(segs, nsegs);
	trav(curr, q){
		auto seg = nsegs.ub(mp(curr, INT_MAX));
		--seg;
		int l = max({1, (seg -> f), curr - (k - 1)}); int r = min(n, l + (k - 1));
		ps(l, r);
	}
}		