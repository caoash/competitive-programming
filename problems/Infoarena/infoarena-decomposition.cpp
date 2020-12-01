/*
 * For this problem, realize the maximum number of factors for an 11 digit number is at most around 4096 or something. Then, realize the product will always be a factor.
 * Let dp[last used factor][product] = number of ways to create a nonincreasing (not nondecreasing, this is important for construction!) sequence and get some product.
 *
 * Once we've computed this, we can then recover the answer by fixing the first number, and then checking whether the number of valid sequences exceeds K, and then updating K.
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
#define f first
#define s second
#define mp make_pair
 
const int MX = 200005;
const int MOD = (int) (1e9 + 7);
const ll INF = (ll) 1e18;
 
namespace output {
    void pr(int x) { cout << x; }
    void pr(long x) { cout << x; }
    void pr(ll x) { cout << x; }
    void pr(unsigned x) { cout << x; }
    void pr(unsigned long x) { cout << x; }
    void pr(unsigned long long x) { cout << x; }
    void pr(float x) { cout << x; }
    void pr(double x) { cout << x; }
    void pr(long double x) { cout << x; }
    void pr(char x) { cout << x; }
    void pr(const char* x) { cout << x; }
    void pr(const string& x) { cout << x; }
    void pr(bool x) { pr(x ? "true" : "false"); }
    
    template<class T1, class T2> void pr(const pair<T1,T2>& x);
    template<class T> void pr(const T& x);
    
    template<class T, class... Ts> void pr(const T& t, const Ts&... ts) { 
        pr(t); pr(ts...); 
    }
    template<class T1, class T2> void pr(const pair<T1,T2>& x) { 
        pr("{",x.f,", ",x.s,"}"); 
    }
    template<class T> void pr(const T& x) { 
        pr("{"); // const iterator needed for vector<bool>
        bool fst = 1; for (const auto& a: x) pr(!fst?", ":"",a), fst = 0; 
        pr("}");
    }
    
    void ps() { pr("\n"); } // print w/ spaces
    template<class T, class... Ts> void ps(const T& t, const Ts&... ts) { 
        pr(t); if (sizeof...(ts)) pr(" "); ps(ts...); 
    }
    
    void pc() { cout << "]" << endl; } // debug w/ commas
    template<class T, class... Ts> void pc(const T& t, const Ts&... ts) { 
        pr(t); if (sizeof...(ts)) pr(", "); pc(ts...); 
    }
    #define dbg(x...) pr("[",#x,"] = ["), pc(x);
}
 
#ifdef LOCAL
using namespace output;
#endif
 
vl divisors;
 
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
gp_hash_table<ll, int> ind;
 
int dp[3050][3050];
int tot[3050];
int go(int i, int j) {
    if (dp[i][j] != -1) {
        return dp[i][j];
    }
    else if (j == sz(divisors)) {
        return dp[i][j] = 0;
    }
    else if (i == 0 && j == sz(divisors) - 1) {
        return dp[i][j] = 1;
    }
    else {
        ll prod = divisors[i];
        ll add = divisors[j];
        int sum = 0;
        if (j != sz(divisors) - 1) sum += go(i, j + 1);
        if (prod % add == 0 && ind.find(prod / add) != ind.end()) {
            sum += go(ind[prod / add], j);
        }
        return dp[i][j] = sum;
    }
}
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    ifstream cin("desc.in");
    ofstream cout("desc.out");
    ll n, k; 
    cin >> n >> k;
    for (ll x = 1; x * x <= n; x++) {
        if (n % x == 0) {
            divisors.pb(x);
            ll y = (n / x);
            if (y != x) {
                divisors.pb(y);
            }
        }
    }
    sort(all(divisors));
    int v = 0;
    for (ll x : divisors) ind[x] = v++;
    int cnt = sz(divisors);
    dp[cnt - 1][0] = 1;
    for (int i = cnt - 1; i > 0; i--) {
        for (int j = 0; j < cnt; j++) {
            ll prod = divisors[j];
            ll add = divisors[i];
            dp[i][j] += dp[i + 1][j];
            if (prod % add == 0 && ind.find(prod / add) != ind.end()) {
                dp[i][j] += dp[i][ind[prod / add]];
            }
        }
    }
    cout << dp[1][cnt - 1] << '\n';
    vector<ll> ans;
    ll fprod = n;
    int prev = 1;
    while (k > 0 && fprod > 1) {
        int _ind = ind[fprod];
        for (int i = prev; i < cnt; i++) {
            int ways = dp[prev][_ind] - dp[i + 1][_ind];
            if (ways >= k) {
                k -= dp[prev][_ind] - dp[i][_ind];
                ans.pb(divisors[i]);
                fprod /= divisors[i];
                prev = i;
                break;
            }
        }
    }
    for (int i = 0; i < sz(ans); i++) {
        cout << ans[i] << " ";
    }
    cout << '\n';
}
