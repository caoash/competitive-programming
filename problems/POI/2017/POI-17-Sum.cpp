/*
Do some digit DP to count number of ways (dp[length][sum][mod m][last digit]), and then try to place each
digit and backtrack to the next state to reconstruct the answer.
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

const int MX = 205;

int S, M; map<array<int, 4>, ll> dp; ll best[MX]; int powt[MX]; ll psum[MX][MX][MX];

ll go(int len, int sum, int mod, int last) {
	if (dp.find({len, sum, mod, last}) != dp.end()) {
		return dp[{len, sum, mod, last}];
	}
	if (sum - last < 0) {
		return dp[{len, sum, mod, last}] = 0;
	}
	if (len == 0) {;
		if (sum == 0 && mod == 0) {
			return dp[{len, sum, mod, last}] = 1;
		}
		return dp[{len, sum, mod, last}] = 0;
	}
	ll add = last * powt[len - 1];
	ll csum = psum[len - 1][sum - last][(mod - (add % M) + (add * M)) % M];;
	for (int prev = 0; prev < 10; prev++) {
		csum += go(len - 1, sum - last, (mod - (add % M) + (add * M)) % M, prev);
	}	
	psum[len][sum][mod] += csum;
	return dp[{len, sum, mod, last}] = csum;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int Q; cin >> S >> M >> Q;
    memset(best, -1, sizeof(best));
    powt[0] = 1;
    for (int i = 1; i <= 200; i++) {
    	powt[i] = (powt[i - 1] * 10) % M;
    }
    while (Q--) {
    	ll k; cin >> k;
    	int l;
    	ll ways = 0;	
    	for (l = 1; l <= 200; l++) {
    		if (best[l] == -1) {
	    		best[l] = 0;
	    		for (int dig = 1; dig <= 9; dig++) {
		    		best[l] += go(l, S, 0, dig);
			    }
			}
    		if (ways + best[l] >= k) {
    			break;
    		}
    		ways += best[l];
    	}
    	if (l > 200) {
    		printf("%s\n", "NIE");
    		continue;
    	}
    	k -= ways;
    	int cmod = 0, csum = S;
    	for (int i = 0; i < l; i++) {
    		ll upto = 0;
    		for (int cdig = (i == 0 ? 1 : 0); cdig < 10; cdig++) {
    			upto += go(l - i, csum, cmod, cdig);
    			if (upto >= k) {
    				k -= (upto - go(l - i, csum, cmod, cdig));
    				printf("%d", cdig);
    				ll add = cdig * powt[l - i - 1];
    				cmod = (cmod - (add % M) + (add * M)) % M;
    				csum = csum - cdig;
    				break;
    			}
    		}	
    	}
    	printf("\n");
    }
}