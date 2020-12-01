/*
First realize it's probably useful to store a mask of whether you released the last 5 animals, and 
on a linear array, this leads to a simple bitmask dp solution where you shift the mask as you move across.

To extend to the circular case, you can brute force the first 4 values which allow you to transition
effectively from the end of the array.
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

const int maxn = 10005, maxc = 50005;

struct Child {
	int st; int state[5];
	bool is_happy(int mask){
		bool happy = false;
		for (int i = 0; i < 5; i++) {
			if (mask & (1 << i)) {
				if (state[4 - i] == 2) {
					happy = true;
				} 
			}
			else {
				if (state[4 - i] == 1) {
					happy = true;
				}
			}
		}
		return happy;
	}	
};

int dp[maxn][(1 << 5)], best[maxn][(1 << 5)];

void solve(){
	int n, c; cin >> n >> c;
	vector<Child> dudes;
	for (int i = 0; i < c; i++) {
		Child curr;	
		cin >> curr.st;
		curr.st--;
		int f, l; cin >> f >> l;
		for (int i = 0; i < 5; i++) {
			curr.state[i] = 0;
		}
		for (int i = 0; i < f; i++) {
			int x; cin >> x;
			x--;
			if (x < curr.st) {
				curr.state[x + (n - curr.st)] = 2;
			}
			else {
				curr.state[x - curr.st] = 2;
			}
		}
		for (int i = 0; i < l; i++) {
			int x; cin >> x;
			x--;
			if (x < curr.st) {
				curr.state[x + (n - curr.st)] = 1;
			}
			else {
				curr.state[x - curr.st] = 1;
			}
		}
		dudes.pb(curr);
	}
	memset(best, 0, sizeof(best));
	for (int mask = 0; mask < (1 << 5); mask++) {
		for (Child curr : dudes) {
			best[(curr.st + 4) % n][mask] += curr.is_happy(mask);
		}
	}
	int ans = 0;
	for (int init = 0; init < (1 << 4); init++) {
		memset(dp, 0, sizeof(dp));
		dp[4][(init << 1) | 1] = best[4][(init << 1) | 1];
		dp[4][(init << 1)] = best[4][(init << 1)];
		for (int i = 5; i < n; i++) {
			for (int mask = 0; mask < (1 << 5); mask++) {
				int fmask = mask >> 1;
				int smask = (mask >> 1) | (1 << 4);
				dp[i][mask] = max(dp[i - 1][fmask], dp[i - 1][smask]) + best[i][mask];
			}
		}
		for (int i = 0; i < 4; i++) {
			for (int mask = 0; mask < (1 << (4 - i)); mask++) {
				int prev = (i - 1 < 0 ? n - 1 : i - 1);
				int nmask = 0;	
				for (int j = 3 - i; j <= 3; j++) {
					if (init & (1 << j)) {
						nmask += (1 << j) >> (4 - (i + 1));
					}
				}
				nmask += (mask << (i + 1));
				int fmask = nmask >> 1;
				int smask = (nmask >> 1) | (1 << 4);
				dp[i][nmask] = max(dp[prev][fmask], dp[prev][smask]) + best[i][nmask];
				if (i == 3) {
					ans = max(ans, dp[i][nmask]);	
				}
			}
		}
	}
	cout << ans << '\n';
}

int main(){
	int t; cin >> t;
	while (t--) {
		solve();
	}
}
