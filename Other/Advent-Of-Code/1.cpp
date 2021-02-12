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
    vi a;
    int x;
    while (cin >> x) a.pb(x);
    for (int i = 0; i < sz(a); i++)
    for (int j = i + 1; j < sz(a); j++)
    for (int k = j + 1; k < sz(a); k++) {
        if (a[i] + a[j] + a[k] == 2020) cout << a[i] * a[j] * a[k] << '\n';
    }
}

