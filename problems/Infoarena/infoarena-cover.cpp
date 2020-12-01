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

vector<pi> pos[1025];
bool used[60005];
int dp[60005];

int main(){
    freopen("cover.in", "r", stdin);
    freopen("cover.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, l; 
    scanf("%d%d", &n, &l);
    vi a(l);
    for (int i = 0; i < l; i++) scanf("%d", &a[i]);
    vector<pi> segs;
    vector<pi> vals;
    for (int i = 0; i < n; i++) {
        int cl, cr; 
        scanf("%d%d", &cl, &cr);
        cl--, cr--;
        vals.pb(mp(cl, cr));
        used[i] = true;
    }
    sort(all(vals));
    int best = INT_MAX;
    for (int i = n - 1; i >= 0; i--) {
        if (vals[i].s >= best) {
            used[i] = false;
            continue;
        }
        best = min(best, vals[i].s);
    }
    for (int i = 0; i < n; i++) {
        if (used[i]) segs.pb(vals[i]);
    }
    int p = 0;
    for (int i = 0; i < l; i++) {
        while (p <= sz(segs) && i > segs[p].s) ++p;
        pos[a[i]].pb(mp(i, p));
    }
    unordered_set<int> need;
    for (int i = 0; i <= 1024; i++) {
        if (pos[i].empty()) continue;
        reverse(all(pos[i]));
        need.insert(i);
    }
    memset(dp, 0x3f3f3f, sizeof(dp));
    dp[0] = 0;
    for (int i = 1; i <= sz(segs); i++) {
        vi rem;
        for (auto j : need) {
            if (pos[j].empty()) continue;
            while (!pos[j].empty() && pos[j].back().f < segs[i - 1].f) pos[j].pop_back();
            if (pos[j].empty()) {
                rem.pb(j);
                continue;
            }
            pi prev = pos[j].back();
            if (prev.f > segs[i - 1].s) continue;
            dp[i] = min(dp[i], dp[prev.s] + j);
        }
        for (auto x : rem) need.erase(x);
    }
    printf("%d", dp[sz(segs)]);
}

