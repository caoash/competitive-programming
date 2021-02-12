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

const int MX = 200005;
const int MOD = (int) (1e9 + 7);
const ll INF = (ll) 1e18;

int brute(int N) {
    ll cur = 1;
    int ans = 0;
    for (int i = 2; i <= N; i++) {
        cur = ((cur * 10) + i) % 3;
        if (cur == 0) ++ans;
    }
    return ans;
}

int solve(int N) {
    if (N > 1) {
        int val = (N - 2) / 3;
        int rem = (N - 2) % 3;
        return (2 * val + 1) + (rem > 0);
    } else {
        return 0;
    }
}

int main(){
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N; cin >> N;
    cout << solve(N) << '\n';
}

