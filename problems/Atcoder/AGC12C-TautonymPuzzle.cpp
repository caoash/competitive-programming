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
    ll N; cin >> N;
    ++N;
    deque<int> ret;
    int cnt = 1;
    vi steps;
    while (N > 1) {
        if (N % 2) {
            steps.pb(1);
            N--;
        } else {
            steps.pb(0);
            N /= 2;
        }
    }
    reverse(all(steps));
    for (auto x : steps) {
        if (x == 0) ret.pb(cnt++);    
        else ret.push_front(cnt++);
    }
    int S = ret.size();
    cout << 2 * S << '\n';
    while (!ret.empty()) {
        cout << ret.front() << ' ';
        ret.pop_front();
    }
    for (int i = 0; i < S; i++) {
        cout << i + 1 << ' ';
    }
    cout << '\n';
}

