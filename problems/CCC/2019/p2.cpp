#include <bits/stdc++.h> 
using namespace std;

typedef long long ll;

#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)

#define F first
#define S second

const int MX = (int) (2e6 + 5);

bool prime[MX];

int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    FOR(i, MX) prime[i] = true;
    prime[0] = false, prime[1] = false;
    F0R(i, 2, MX) {
        if (prime[i] && (ll) (i * i) <= MX) {
            for (ll j = i * i; j <= MX; j += i) {
                prime[j] = false;
            }
        } else if ((ll) (i * i) > MX) {
            break;
        }
    }
    vector<ll> prims;
    FOR(i, MX) {
        if (prime[i]) prims.push_back(i);
    }
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        for (auto x : prims) {
            if (x <= 2 * n) {
                if (prime[2 * n - x]) {
                    cout << x << " " << 2 * n - x << '\n';
                    break;
                }
            }
        }
    }
}

