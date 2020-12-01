/*
Rather than computing whether you can get some sum of weights, which is difficult to reverse, compute the number
of ways to achieve some weights. Then, you can just do the DP backwards to reverse it (see code). 

After reversing it, we need to find the smallest weight such that it's not the difference between two possible
weights you can achieve. Realize that the difference between two possible weights is just some weight added with
-1 * some other weight. In other words, we can just run the DP again over the negative values to check which weights
can be made as a difference, and take the smallest.
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

const int maxn = 105, maxw = 700000, mod = (int) 1e9 + 7;

ll dp[maxw + 5], b[maxn];

int main(){
	int n; cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> b[i];
	}
	dp[0] = 1;
	for (int i = 0; i < n; i++) {
		for (int j = maxw - 1; j >= 0; j--) {
			if (j - b[i] >= 0){
				dp[j] += dp[j - b[i]];
				dp[j] %= mod;
			}
		}
	}

	int ans = 0, best = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < maxw; j++){
			if (j - b[i] >= 0) {
				dp[j] -= dp[j - b[i]];
				dp[j] += mod;
				dp[j] %= mod;
			}
		}	
		int cnt = 0;
		for (int j = 0; j < maxw; j++) {
			cnt += (dp[j] > 0);
		}
		if(cnt > ans){
			ans = cnt;
			best = i;
		}
		else if(cnt == ans){
			if(b[i] < b[best]){
				best = i;
			}
		}
		for (int j = maxw - 1; j >= 0; j--){
			if (j - b[i] >= 0) {
				dp[j] += dp[j - b[i]];
				dp[j] %= mod;
			}
		}
	}

	for (int j = 0; j < maxw; j++) {
		if (j - b[best] >= 0) {
			dp[j] -= dp[j - b[best]];
			dp[j] %= mod;
		}
	}

	for (int i = 0; i < n; i++) {
		if (i != best) {
			for (int j = 0; j < maxw; j++) {
				if (j + b[i] < maxw) {
					dp[j] += dp[j + b[i]];
					dp[j] %= mod;
				}
			}
		}
	}

	int q = 1;	
	while (dp[q] > 0) {
		++q;
	}
	cout << b[best] << " " << q << "\n";
}