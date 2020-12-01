/*
Observe that two points will be seen by one line segment if they have the same slope to some guard.

So, let's say that the x distance to a guard for some point is dx and y distance is dy. If dx and dy
can be further reduced by dividing by a factor, then it shares slope with the point divided by that
factor. In other words, if dx and dy are relatively prime, then they will be seen by the guard.

Let's iterate over y, and count how many x from 1 ... L are relatively prime to this y for the guards.
The function get(x, L) calculates this.

So, for some y, let dy1 equal the y distance to the first guard and dy2 the distance to the second guard.

Then, to calculate:
number of super secure vaults - some vault is super secure if both dy1 and dy2 are relative prime to it.
In other words, (dy1 * dy2) is relatively prime to it, so it's just equal to get(dy1 * dy2, L).

number of secure vaults - get(dy1, L) + get(dy2, L) except you overcount the super secure vaults so subtract
get (dy1 * dy2, L)

number of insecure vaults = L - # secure vaults = L - (get(dy1, L) + get(dy2, L) - get(dy1 * dy2, L)) = 
L - get(dy1, L) - get(dy2, L) + get(dy1 * dy2, L). This also makes sense because it's total vaults minus
number of vaults each guard sees, except you undercount the super secure vaults so add it.

Now the question is, how do you implement get()?

First of all, it's much easier to count the number of numbers not relatively prime to some A from 1 ... L, 
so do that and subtract it from L. Then, some factor X of A has L / X numbers which are not relatively prime to A.

So the solution is, for every factor of X, sum up L / X. Then subtract for odd number of factors, add even, 
(due to principal of inc/exc). However, some number can have too many factors to do this, so do it with 
only prime factors since any number X which you use can be created by some smaller prime factor (or it is prime).
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

vi gf(int x) {
	vi ret;
	if (x % 2 == 0) {
		ret.pb(2);
		while (x % 2 == 0) {
			x /= 2;
		}
	}
	for (int i = 3; i <= sqrt(x); i += 2) {
		if (x % i == 0) {
			ret.pb(i);
			while (x % i == 0) x /= i;
		}
	}
	if (x > 2) ret.pb(x);
	return ret;
}

ll get(ll a, ll b) {
	if (a == 0) return 0;	
	if (a == 1) return b;
	vi cf = gf(a);
	int m = sz(cf);
	ll tot = 0;
	for (int i = 1; i < (1 << m); i++) {
		int mult = (__builtin_popcount(i) % 2 == 0 ? -1 : 1);
		for (int j = 0; j < m; j++) {
			if (i & (1 << j)) {
				mult *= cf[j];
			}
		}
		tot += (b / mult);
	}
	return b - tot;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int A, B; cin >> A >> B;
    ll L; cin >> L;
    vector<ll> ans(3);
    for (int i = -A; i <= B; i++) {
    	int da = (i - (-A)); int db = B - i;
    	ll rpf = get(da, L);
    	ll rps = get(db, L);
    	ll rpt = get(da * db, L);
    	ans[0] += rpt;
    	ans[1] += rpf + rps - (2 * rpt);
    	ans[2] += L - rpf - rps + rpt;
    }
    ans[0] += 2, ans[1] -= 2;
    printf("%lld\n%lld\n%lld\n", ans[2], ans[1], ans[0]);
}