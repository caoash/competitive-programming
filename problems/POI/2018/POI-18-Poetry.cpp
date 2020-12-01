/*
Start by transforming a[i] -> (a[i] + 1) mod s. This doesn't change the answer and guarantees values are < s.

Start with the second subtask, where values are unique. Realize you can always achieve an answer of 0 by just adding values
in any order until one makes you reach s - 1, and then add another value. If there is no other value, then the current
value is the last one, which doesn't count towards the answer so you just use it and get 0.

-- I READ EDITORIAL HERE -- 

By doing this subtask, you develop the intuition that having a lot of distinct values is a good thing. In fact, you always
prefer some remaining values with the maximum number of distinct values. The simple "proof" (mostly intuition) for this is that
if the maximum number of distinct values when you have X values remaining is Y, and taking some value a_i leads to s - 1, then
take some other value a_j. If no other value exists, then that means there's 1 distinct value and we assumed we have the maximum number,
of distinct values, which means that 1 is the maximum number of distinct values that can remain. Therefore, there will never be an 
answer with X values if you can't achieve one with the max distinct values.

So, the algorithm becomes keep taking the value that appears the most, unless it leads to s - 1. Then, take the value that appears 
the second most (which is different than the one that appears most). 
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

vi vals[1000001]; map<int, int> freq;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);	
    int n, s; cin >> n >> s;
    priority_queue<pi> pq;
    for (int i = 0; i < n; i++) {
    	int x; cin >> x;	
    	x++, x %= s;
    	vals[x].pb(i);
    	freq[x]++;
    }
    for (auto curr : freq) {
    	pq.push(mp(curr.s, curr.f));
    }
    vi ret;
    int sum = 0; int ans = 0;
    while (!pq.empty()) {
    	pi curr = pq.top(); pq.pop();
    	if (((sum + curr.s) % s) == s - 1) 	{
    		if(!pq.empty()){
    			pi nxt = pq.top(); pq.pop();
    			sum += nxt.s; sum %= s;
    			ret.pb(vals[nxt.s].back());
	    		vals[nxt.s].pop_back();	
    			if(nxt.f - 1 != 0) pq.push(mp(nxt.f - 1, nxt.s));
    			pq.push(curr);
    		}
    		else {
    			sum = 0;
    			ret.pb(vals[curr.s].back());
	    		vals[curr.s].pop_back();
    			if(curr.f - 1 != 0) {
    				pq.push(mp(curr.f - 1, curr.s));
    				++ans;
    			}
    		}
    	}
    	else {
    		ret.pb(vals[curr.s].back());
    		vals[curr.s].pop_back();
    		sum += curr.s; sum %= s;
    		if(curr.f - 1 != 0) pq.push(mp(curr.f - 1, curr.s));
    	}
    }
    cout << ans << '\n';
    for (int x : ret){
    	cout << x + 1 << " ";
    }
}