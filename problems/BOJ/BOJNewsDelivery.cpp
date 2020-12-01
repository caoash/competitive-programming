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
#define f first
#define s second
#define mp make_pair

const int MX = 200005;
const int MOD = (int) (1e9 + 7);
const ll INF = (ll) 1e18;

vi adj[MX];
int dp[MX];

void dfs(int v, int p) {
    vi cv;
    for (int to : adj[v]) {
        if (to != p) {
            dfs(to, v);
            cv.pb(dp[to]);
        }
    }
    sort(all(cv));
    reverse(all(cv));
    for (int i = 0; i < sz(cv); i++) {
        dp[v] = max(dp[v], cv[i] + i + 1);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    int root = 0;
    for (int i = 0; i < n; i++) {
        int p; cin >> p;
        if (p == -1) {
            root = i;
            continue;
        }
        adj[p].pb(i);
    }
    dfs(root, -1);
    cout << dp[root] << '\n';
}

