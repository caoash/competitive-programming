/*
 * Fracturing search. Same as usaco.guide/adv/fracture.
 *
 * In a fracturing search problem we need to define states / transitions such that:
 * a.) the resulting graph is a tree
 * b.) for any node v, the subtree of v has values greater than or equal to v.
 *
 * The first idea I tried for this problem is just store a vector of what part you are on for each location, and
 * transition by increasing the index by one. This doesn't work because there can be cycles meaning it's not a tree.
 * For example: 1 1 1 -> 1 2 1 -> 2 2 1 is the same as 1 1 1 -> 2 1 1 -> 2 2 1 where the numbers denote which part you took.
 *
 * The second idea was to store which part you are on for each location (denoted as i, j), and do the following transitions:
 * a.) Move to the next location if j != 0, since moving if j = 0 would just lead to the same state which is bad because the robot isn't different.
 * b.) If j = 1, set j = 0 and increase 1, then set j to 1. Pretty much move back to the first part and go to the next location with the second part.
 * c.) Move to the next part.
 * This leads to a tree structure, but doesn't satisfy the second requirement that the nodes in the subtree must be greater than or equal.
 * This is because of the second transition. If you replace the current part with the location + 1 part, the value changes by (curr value - new value). 
 * If the parts aren't sorted, we get a better state in the subtree, which is bad.
 *
 * Luckily, to fix this, we just need to sort the parts to ensure the subtree has better values and distinct robots.
 */

#include <bits/stdc++.h> 
using namespace std;

using ll = long long;

using vi = vector<int>;
using vl = vector<ll>;
#define pb push_back
#define rsz resize
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using pi = pair<int,int>;
using T = pair<ll, pi>;
#define f first
#define s second
#define mp make_pair

const int MX = 200005;
const int MOD = (int) (1e9 + 7);
const ll INF = (ll) 1e18;

vector<vi> pos;
priority_queue<T, vector<T>, greater<T>> pq;

int main(){
    ifstream cin("roboherd.in");
    ofstream cout("roboherd.out");
    int n, k; cin >> n >> k;
    ll num = 0;
    for (int i = 0; i < n; i++) {
        int m; cin >> m;
        vi curr(m);
        for (int j = 0; j < m; j++) {
            cin >> curr[j];
        }
        sort(all(curr));
        num += curr[0];
        for (int j = m - 1; j >= 0; j--) {
            curr[j] -= curr[0];
        }
        if (sz(curr) > 1) pos.pb(curr);
    }
    sort(all(pos));
    pq.push({0, {0, 0}});
    ll tot = 0;
    while (!pq.empty()) {
        if (k == 0) {
            break;
        }
        k--;
        T curr = pq.top();
        pq.pop();
        tot += (num + curr.f);
        if (curr.s.s < sz(pos[curr.s.f]) - 1) {
            pq.push({curr.f - pos[curr.s.f][curr.s.s] + pos[curr.s.f][curr.s.s + 1], {curr.s.f, curr.s.s + 1}});
        }
        if (curr.s.f < sz(pos) - 1) {
            if (curr.s.s == 1) pq.push({curr.f - pos[curr.s.f][1] + pos[curr.s.f + 1][1], {curr.s.f + 1, curr.s.s}});
            if (curr.s.s) pq.push({curr.f + pos[curr.s.f + 1][1], {curr.s.f + 1, 1}});
        }
    }
    cout << tot << '\n';
}

