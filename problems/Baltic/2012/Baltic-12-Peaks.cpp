/*
First preprocess the peaks by taking each connected region (find with BFS) and marking exactly one of them as
(grid[x][y], 1) while the others as (-1, -1) where the pairs store (value of maximum peak, how many peaks).

Then, go in nonincreasing order of value and merge with DSU, modifying the merge function to update the pair
accordingly and adding to the answer accordingly.
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
const int MX = 2005;
const ld PI = 4*atan((ld)1);

int n, m; int grid[MX][MX]; vpi ans; bool peak[MX][MX], done[MX][MX], vis[MX][MX];

template<int SZ> struct DSU{
	int p[SZ], sz[SZ]; pi best[SZ];
	void init(){
		for(int i = 0; i < n * m; i++){
			p[i] = i; sz[i] = 1; 
			if(peak[i / m][i % m]) {
				best[i] = mp(grid[i / m][i % m], 1);
			}
			else{
				best[i] = mp(-1, -1);
			}
		}
	}
	int find(int x){
		return p[x] = (p[x] == x ? x : find(p[x]));
	}
	pi gbst(int u){
		return best[find(u)];
	}
	void merge(int u, int v, int x){
		int a = find(u); int b = find(v);
		if(a != b){
			if(sz[a] < sz[b]){
				swap(a,b);
			}
			p[b] = a;
			sz[a] += sz[b];
			// dbg(a / m, a % m, b / m, b % m, best[a], best[b]);
			if(best[b].f == best[a].f){
				// dbg("EQ");
				best[a] = mp(best[a].f, best[b].s + best[a].s);
			}
			else if(best[b].f > best[a].f){
				if(best[a].f != -1) {
					// dbg("ADDING", a / m, a % m, best[a], x);
					fax(i, best[a].s) ans.pb(mp(best[a].f, x));
				}
				best[a] = best[b];
			}
			else if(best[a].f > best[b].f){
				if(best[b].f != -1) {
					// dbg("ADDING", b / m, b % m, best[b], x);
					fax(i, best[b].s) ans.pb(mp(best[b].f, x));
				}
			}
			// dbg(a / m, a % m, b / m, b % m, best[a]);
		}
	}
};


int id(int x, int y){return m * x + y; }

DSU<MX * MX> d;

const int dx[] = {1, 0, -1, 0, 1, -1, 1, -1}, dy[] = {0, 1, 0, -1, 1, 1, -1, -1};

int main() {
    setIO(); 
    re(n, m);
    vpi vals;
    fax(i, n){
    	fax(j, m){
    		re(grid[i][j]);
    		vals.pb(mp(i, j));
    	}
    }
    sort(all(vals), [&](const pi &a, const pi &b){
    	return grid[a.f][a.s] < grid[b.f][b.s];
    });
    fax(i, n){
    	fax(j, m){
    		if(vis[i][j]) continue;
    		peak[i][j] = true;
    		vi cells;
    		queue<pi> bfs;
    		bfs.push(mp(i, j));
    		while(!bfs.empty()){
    			pi curr = bfs.front(); bfs.pop();
    			if(!vis[curr.f][curr.s]){
    				fax(k, 8){
    					int nx = curr.f + dx[k], ny = curr.s + dy[k];
    					if(nx >= 0 && nx < n && ny >= 0 && ny < m){
							if(!vis[nx][ny] && grid[nx][ny] == grid[curr.f][curr.s]){
	    						bfs.push(mp(nx, ny));
	    					}
    					}
    				}
    			}
    			vis[curr.f][curr.s] = true;
    			cells.pb(id(curr.f, curr.s));
    		}
    		trav(curr, cells){
    			int cx = curr / m, cy = curr % m;
    			fax(k, 8){
    				int nx = cx + dx[k], ny = cy + dy[k];
    				if(nx >= 0 && ny >= 0 && nx < n && ny < m){
    					if(grid[nx][ny] > grid[cx][cy]){
    						peak[i][j] = false;
    					}
    				}
    			}
    		}
    	}
    }
    d.init();
    /*
    fax(i, n){
    	fax(j, m){
    		pr(peak[i][j] ? 1 : 0, " ");
    	}
    	ps();
    }
    */
    // cout << endl;
    reverse(all(vals));
    trav(curr, vals){
    	int ind = id(curr.f, curr.s); 
    	set<int> pars;
    	// dbg(grid[curr.f][curr.s]);
    	fax(i, 8){
    		int nx = curr.f + dx[i], ny = curr.s + dy[i];	
    		if(nx >= 0 && ny >= 0 && nx < n && ny < m){
	    		// dbg(nx, ny, done[nx][ny]);
    			if(d.find(ind) != d.find(id(nx, ny))
    				&& done[nx][ny]){
	    			pars.insert(d.find(id(nx, ny)));
	    		}
    		}
    	}
    	// dbg(curr.f, curr.s, pars);
		trav(to, pars){
			d.merge(ind, to, grid[curr.f][curr.s]);
		}
		done[curr.f][curr.s] = true;
    }
    pi fin = d.gbst(id(0, 0));
    fax(i, fin.s) ans.pb(mp(fin.f, 0));
    sort(all(ans)); reverse(all(ans));
    ps(sz(ans));
    trav(curr, ans){
    	ps(curr.f, curr.s);
    }
}