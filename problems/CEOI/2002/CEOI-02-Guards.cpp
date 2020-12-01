/*
 * Can turn problem into max matching since placing a guard technically "satsifies" one row and one column segment, so draw an edge between them and use
 * augmenting paths.
 */

#include <bits/stdc++.h> 
using namespace std;

using ll = long long;

using vi = vector<int>;
using vl = vector<ll>;
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define lb lower_bound
#define ub upper_bound

using pi = pair<int,int>;
#define f first
#define s second
#define mp make_pair

const int MX = 205;
const int MOD = (int) (1e9 + 7);
const ll INF = (ll) 1e18;

int id[MX][MX][2];
int grid[MX][MX];
vi adj[MX * MX];
map<pi, pi> rev;
int was[MX * MX];
int pa[MX * MX], pb[MX * MX];
int it = 0;

bool dfs(int c){
	was[c] = it;
	for(int i : adj[c]){
		if(pb[i] == -1){
			pa[c] = i;
			pb[i] = c;
			return 1;
		}
	}
	for(int i : adj[c]){
		if(was[pb[i]] != it && dfs(pb[i])){
			pa[c] = i;
			pb[i] = c;
			return 1;
		}
	}
	return 0;
}

int main(){
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m; cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];    
        }
    }
    int cur = 1;
    bool seen = false;
    set<int> nods;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 2) {
                cur += seen;
                seen = false; 
            } else {
                id[i][j][0] = cur;
                nods.insert(cur);
                seen = true;
            }
        }
        cur += seen;
        seen = false;
    }
    cur = 1;
    seen = false;
    set<int> snods;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[j][i] == 2) {
                cur += seen;
                seen = false;
            } else {
                id[j][i][1] = cur;
                snods.insert(cur);
                seen = true;
            }
        }
        cur += seen;
        seen = false;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j]) continue;
            int u = id[i][j][0], v = id[i][j][1];
            adj[u].pb(v);
            rev[mp(u, v)] = mp(i, j);
        }
    }
    int ret = 0, add;
	memset(pa, -1, sizeof(pa));
	memset(pb, -1, sizeof(pb));
	do {
		add = 0;
		it++;
        for (auto i : nods) {
			if(pa[i] == -1 && dfs(i)) {
                add++;
            }
		}
		ret += add;
	} while(add);
    cout << ret << '\n';
    for (auto i : nods) {
        if (pa[i] != -1) {
            pi go = rev[mp(i, pa[i])];
            cout << go.f + 1 << " " << go.s + 1 << '\n';
        }
    }
}

