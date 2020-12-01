/*
Some fixed ratio x is achievable if (total profit) / (total length) >= x. Rewrite the condition as (total profit) >= x * total length,
or total profit - x * total length >= 0. If we add N ^ 2 edges, such that the cost of (a, b) is (best profit from a, b) - x * (length),
then we just need to detect a nonnegative weight cycle. Multiply edges by -1 and use floyd warshall to find the shortest path from x to itself.
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
const int MX = 205;
const ld PI = 4*atan((ld)1);

int n; ll c[MX][2005][2]; ll sp1[MX][MX], sp2[MX][MX]; ll best[MX][MX];

int main() {
    setIO(); 
   	int m, k; re(n, m, k); 	 
   	fax(i, n){
	   	fax(j, k){
	   		re(c[i][j][0], c[i][j][1]);	
	   	}
    }
   	fax(i, n) fax(j, n) sp1[i][j] = sp2[i][j] = INF;
   	fax(i, m){
   		int u, v, w; re(u, v, w);
   		u--, v--;
   		sp1[u][v] = w;
   	}
	fax(md, n){
		fax(i, n){
			fax(j, n){
				sp1[i][j] = min(sp1[i][j], sp1[i][md] + sp1[md][j]);	
			}
		}
	}
   	fax(i, n){
   		fax(j, n){
   			fax(t, k){
   				if(c[i][t][0] != -1 && c[j][t][1] != -1){
	   				ckmax(best[i][j], c[j][t][1] - c[i][t][0]);
	   			}
   			}
   		}
   	}
   	ll lo = 1; ll hi = 1e9; ll ans = 0;
   	for(int it = 0; it < 60; it++){
   		ll mid = (lo + hi) / 2;
   		fax(i, n){
   			fax(j, n){
   				sp2[i][j] = -1LL * (best[i][j] - (mid * min(sp1[i][j], INF/mid/2)));
   			}
   		}
   		fax(md, n){
			fax(i, n){
				fax(j, n){
					sp2[i][j] = min(sp2[i][j], sp2[i][md] + sp2[md][j]);	
				}
			}
		}
   		bool ok = false; 
   		fax(i, n){
   			ok |= sp2[i][i] <= 0;
   		}
   		if(ok){
   			lo = mid + 1;
   			ans = mid;
   		}
   		else{
   			hi = mid - 1;
   		}
   	}
   	ps(ans);
}