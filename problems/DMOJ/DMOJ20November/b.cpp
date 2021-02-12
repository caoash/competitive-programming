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

const int MX = 1000005;
const int MOD = (int) (1e9 + 7);
const ll INF = (ll) 1e18;

int fir[MX], last[MX];

int main(){
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m; cin >> n >> m;
    memset(fir, -1, sizeof(fir));
    memset(last, -1, sizeof(last));
    for (int i = 0; i < n; i++) {
        int ci; cin >> ci;
        if (fir[ci] == -1) fir[ci] = i;
        last[ci] = i;
    }
    int ans = 0;
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        if (fir[a] != -1 && last[b] != -1) ans = max(last[b] - fir[a] + 1, ans);
    }
    cout << ans << '\n';
}

