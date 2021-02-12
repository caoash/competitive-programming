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

int main(){
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    string f;
    int ans = 0;
    while (cin >> f) {
        array<string, 2> vals;
        int p = 0;
        for (int i = 0; i < sz(f); i++) {
            if (f[i] == '-') {
                ++p; 
                continue;
            }
            vals[p] += f[i];
        }
        int a = stoi(vals[0]), b = stoi(vals[1]);
        cin >> f;
        char c = f[0];
        cin >> f;
        int cnt = 0;
        for (auto x : f) if (x == c) ++cnt;
        cout << f << '\n';
        if ((f[a - 1] != c && f[b - 1] == c) || (f[a - 1] == c && f[b - 1] != c)) {
            ++ans;
        }
    }
    cout << ans << '\n';
}

