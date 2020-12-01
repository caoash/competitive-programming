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

const int MX = 100005;
const int MOD = (int) (1e9 + 7);
const ll INF = (ll) 1e18;

int main(){
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    stack<int> s1, s2;
    s1.push(INT_MAX);
    s2.push(INT_MAX);
    int need = 1;
    vi ret(n);
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        if (x < s1.top() && x < s2.top()) {
            if (s1.top() <= s2.top()) s1.push(x), ret[i] = 1;
            else s2.push(x), ret[i] = 2;
        } else if (x < s1.top()) {
            s1.push(x), ret[i] = 1;
        } else if (x < s2.top()) {
            s2.push(x), ret[i] = 2;
        } else {
            cout << "NIE" << '\n';
            return 0;
        }
        while (1) {
            bool done = true;
            if (s1.top() == need) ++need, s1.pop(), done = false;
            if (s2.top() == need) ++need, s2.pop(), done = false;
            if (done) break;
        }
    }
    while (1) {
        bool done = true;
        if (s1.top() == need) ++need, s1.pop(), done = false;
        if (s2.top() == need) ++need, s2.pop(), done = false;
        if (done) break;
    }
    if (need <= n) {
        cout << "NIE" << '\n';
        return 0;
    }
    cout << "TAK" << '\n';
    for (int i = 0; i < n; i++) cout << ret[i] << " ";
}

