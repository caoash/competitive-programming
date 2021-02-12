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

void solve() {
    int N; cin >> N;
    vi a(N);
    vi cnt(N + 1);
    bool bad = false;
    for (int i = 0; i < N; i++) {
        cin >> a[i];
        cnt[a[i]]++;
        if (cnt[a[i]] > (N + 1) / 2) {
            bad = true;
        }
    }
    if (bad) {
        cout << -1 << endl;
        return;
    }
    for (int i = 0; i <= N; i++) cnt[i] = 0;
    int ans = 0;
    for (int i = 0; i < N - 1; i++) {
        if (a[i] == a[i + 1]) {
            ++ans;
            cnt[a[i]]++;
            cnt[a[i + 1]]++;
        }
    }
    cnt[a[0]]++;
    cnt[a[N - 1]]++;
    int tot = 0, mx = 0;
    for (int i = 1; i <= N; i++) {
        if (cnt[i] > mx) mx = cnt[i];
        tot += cnt[i];
    }
    ans += max(0, (mx - (tot - mx) - 2) / 2);
    cout << ans << '\n';
}

int main(){
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T; cin >> T;
    while (T--) {
        solve();
    }
}

