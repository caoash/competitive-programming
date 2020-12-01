/*
Work in progress, currently isn't complete. Implementation is kind of bad...
*/

#include <bits/stdc++.h> 
using namespace std;

using ll = long long;

using vi = vector<int>;
#define pb push_back
#define rsz resize
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using pi = pair<int,int>;
#define f first
#define s second
#define mp make_pair

const int MX = 200005;
const int MOD = (int) 1e9 + 7;

template<class T, int SZ> struct Seg{
	T tree[4*SZ];
	T merge(T a, T b){
		if (a.f == b.f) {
			return mp(a.f, a.s + b.s);
		}
		else {
			return (a.f < b.f ? a : b);
		}
	}
	void build(int v, int l, int r) {
		if (l == r) {
			tree[v] = mp(INT_MAX, 0);
		}
		else {
			int mid = (l + r) / 2;
			build(2 * v + 1, l, mid);
			build(2 * v + 2, mid + 1, r);
			tree[v] = merge(tree[2 * v + 1], tree[2 * v + 2]);
		}
	}
	void update(int v, int l, int r, int i, T x) {
		if (i > r || i < l) {
			return;
		} else if (l == r) {
			tree[v] = merge(tree[v], x);
		} else {
			int m = (l + r) / 2;
			update(2 * v + 1, l, m, i, x);
			update(2 * v + 2, m + 1, r, i, x);
			tree[v] = merge(tree[2 * v + 1], tree[2 * v + 2]);
		}
	}

	T query(int v, int l, int r, int ql, int qr) {
		if (l > qr || r < ql) {
			return mp(INT_MAX, 0);
		} else if (l >= ql && r <= qr) {
			return tree[v];
		} else {
			int m = (l + r) / 2;
			T a = query(2 * v + 1, l, m, ql, qr);
			T b = query(2 * v + 2, m + 1, r, ql, qr);
			return merge(a,b);
		}
	}
};

int m, n; map<int, int> cc; Seg<pair<ll, ll>, MX> orz; pair<ll, ll> dp[MX];

void upd(int i, pair<ll, ll> x){
	dp[i] = x;
	orz.update(0, 0, cc[m], i, x);
}

int st[MX], en[MX];

void solve(){
	cin >> m >> n;		
	vector<pi> pts;
	set<int> vals, sts; 
	vals.insert(0);
	vector<pi> init;
	for (int i = 0; i < n; i++) {
		int a, b; cin >> a >> b;
		init.pb(mp(a, b));
	}
	sort(all(init));
	stack<pi> proc;
	for (int i = 0; i < n; i++) {
		while(!proc.empty() && proc.top().s >= init[i].s) {
			proc.pop();
		}
		proc.push(init[i]);
	}
	while (!proc.empty()) {
		pts.pb(proc.top());
		proc.pop();
	}
	n = sz(pts);
	for (int i = 0; i < n; i++) {
		int a = pts[i].f, b = pts[i].s;
		vals.insert(a), vals.insert(b + 1);
		sts.insert(a);
		dp[i] = mp(INT_MAX, 0);
	}
	vals.insert(m);
	orz.build(0, 0, cc[m]);
	sort(all(pts), [&](const pi &fst, const pi &sc){
		return fst.s == sc.s ? fst.f < sc.f : fst.s < sc.s;
	});
	int cnt = 0;
	for (int x : vals) {
		cc[x] = cnt++;
	} 
	for (int i = 1; i < n; i++) {
		
	}
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T; cin >> T;
   	while (T--) {
   		solve();
   	} 
}