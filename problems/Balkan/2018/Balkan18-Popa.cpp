/*
Same as editorial. Use query (x, i, i, i) to check if some node can be the root of some subtree.

Construct them one by one and when adding some value, go up the chain to the root and add to the highest valid one.
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

int solve(int N, int *L, int *R) {
    vector<int> st;
    st.pb(0);
    L[0] = R[0] = -1;
    for (int i = 1; i < N; i++) {
        L[i] = -1, R[i] = -1;
        while (!st.empty() && query(st.back(), i, i, i)) {
            L[i] = st.back();
            st.pop_back();
        }
        if (!st.empty()) {
            R[st.back()] = i;
        }
        st.pb(i);
    }
    return st.front();
}