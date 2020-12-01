/*
Create a directed graph over the game states (cop location, robber location, turn) and update starting at (x, x, 0) and (x, x, 1).

Then, if all the states a robber goes to are winningm, the state is winning. Otherwise, if any state a cop can go to is winning, then the state is winning.
*/

#include <bits/stdc++.h>

using namespace std;
 
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
const int MX = 500;
const ld PI = 4*atan((ld)1);
const int WIN = 1, LOSE = 2;

vector<pii> rev[MX][MX][2]; int deg[MX], cnt[MX][MX]; pii go[MX][MX][2]; int gst[MX][MX][2]; 

int ret = -1;

int start(int N, bool A[MX][MX]){
	fax(i, N) fax(j, N) gst[i][j][0] = gst[i][j][1] = LOSE;
	fax(i, N) {
		fax(j, N){
			deg[i] += A[i][j];
		}	
	}
	queue<pii> st;
	fax(i, N) {
		gst[i][i][0] = gst[i][i][1] = WIN;
		st.push(mp(i, mp(i, 0)));
		st.push(mp(i, mp(i, 1)));
	}	
	while(!st.empty())	{
		pii curr = st.front(); st.pop();
		if(gst[curr.f][curr.s.f][curr.s.s] == WIN){
			fax(i, N){
				if(curr.s.s == 0 && (A[curr.f][i] || i == curr.f)){
					pii to = mp(i, mp(curr.s.f, 1));
					if(gst[to.f][to.s.f][to.s.s] == WIN) continue;
					go[to.f][to.s.f][to.s.s] = mp(curr.f, mp(curr.s.f, curr.s.s));
					gst[to.f][to.s.f][to.s.s] = WIN;
					st.push(mp(to.f, mp(to.s.f, to.s.s)));
				}
				if(curr.s.s == 1 && A[curr.s.f][i]){
					pii to = mp(curr.f, mp(i, 0));
					if(gst[to.f][to.s.f][to.s.s] == WIN) continue;
					cnt[to.f][to.s.f]++;
					if(cnt[to.f][to.s.f] == deg[to.s.f]){
						gst[to.f][to.s.f][to.s.s] = WIN;
						go[to.f][to.s.f][to.s.s] = mp(curr.f, mp(curr.s.f, curr.s.s));
						st.push(mp(to.f, mp(to.s.f, to.s.s)));
					}
				}
			}
		}
	}
	fax(i, N){
		fax(j, N){
			if(gst[i][j][0] != WIN){
				break;
			}
			if(j == N - 1){
				ret = i;
			}
		}
	}
	return ret;
}

int nextMove(int R){
	// dbg(go[ret][R][0]);
	return ret = go[ret][R][0].f; 
}
int main() {
    setIO(); 
    int N; re(N);
	bool inp[MX][MX];
    fax(i, N){
    	fax(j, N){
    		re(inp[i][j]);
    	}
    }
    ps(start(N, inp));
    cout << endl;
    int r; re(r);
    while(r != -1){
    	ps(nextMove(r));
    	cout << endl;
    	re(r);
    }
}
