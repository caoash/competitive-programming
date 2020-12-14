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
    int n; cin >> n;
    vi a(n);
    vector<bool> bad(n);
    for (auto &x : a) cin >> x;
    sort(all(a));
    int diam = a[sz(a) - 1];
    if (diam % 2) {
        bool good = true; 
        for (int x = (diam + 1) / 2; x <= diam; x++) {
            bool found = false;
            for (int i = 0; i < n; i++) {
                for (int j = i + 1; j < n; j++) {
                    if (a[i] == x && a[j] == x) {
                        found = true;
                        bad[i] = true;
                        bad[j] = true;
                        break;
                    }
                }
                if (found) break;
            }
            good &= found;
        }
        for (int i = 0; i < n; i++) {
            if (bad[i]) continue;
            good &= (a[i] >= (diam + 1) / 2 + 1);
        }
        cout << (good ? "Possible" : "Impossible") << '\n';
    } else {
        bool good = true;
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (a[i] == (diam / 2)) {
                bad[i] = true;
                found = true;
                break;
            }
        }
        good &= found;
        for (int x = (diam / 2) + 1; x <= diam; x++) {
            found = false;
            for (int i = 0; i < n; i++) {
                for (int j = i + 1; j < n; j++) {
                    if (a[i] == x && a[j] == x) {
                        bad[i] = true;
                        bad[j] = true;
                        found = true; 
                        break;
                    }
                }
                if (found) break;
            }
            good &= found;
        }
        for (int i = 0; i < n; i++) {
            if (bad[i]) continue;
            good &= (a[i] >= (diam / 2 + 1));
        }
        cout << (good ? "Possible" : "Impossible") << '\n';
    }
}

