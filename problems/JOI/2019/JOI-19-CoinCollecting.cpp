/*
 * First observe that if you pair some coins to their final locations, it's always optimal to take Manhattan distance.
 *
 * Let's start by moving all the coins into the box by moving them to their closest location. This doesn't hurt the answer since any future moves to any other location
 * still follow Manhattan distance.
 *
 * Now you have coins (maybe > 1 in a cell) in a grid of 2 * N. You can apply a greedy where you move left to right and start by filling the row a coin is on.
 * Then once you've done that for both the top and bottom, you can try to fill the other row. You can prove this with exchange arguments.
 */

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

int num[2][MX];

int main(){
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    ll ans = 0;
    for (int i = 0; i < 2 * n; i++) {
        ll x, y; cin >> x >> y;
        ll go = x - 1;
        if (go < 0) ans += abs(go), go = 0;
        if (go >= n) ans += go - n + 1, go = n - 1;
        if (y <= 1) {
            ans += abs(y - 1);
            num[0][go]++;
        } else {
            ans += abs(y - 2);
            num[1][go]++;
        }
    }
    array<int, 2> pt;
    pt[0] = 0, pt[1] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2; j++) {
            int &need = pt[j];    
            while (need < i && num[j][i] > 1) {
                if (num[j][need] == 0) {
                    num[j][i]--;
                    num[j][need]++;
                    ans += abs(i - need);
                }
                ++need;
            }
        }
        for (int j = 0; j < 2; j++) {
            int &need = pt[j ^ 1];
            while (need < i && num[j][i] > 1) {
                if (num[j ^ 1][need] == 0) {
                    num[j][i]--;
                    num[j ^ 1][need]++;
                    ans += 1 + abs(i - need);
                }
                ++need;
            }
            if (num[j][i] > 1 && num[j ^ 1][i] == 0) {
                ++ans;
                num[j][i]--;
                num[j ^ 1][i]++;
            }
            if (num[j][i] > 1 && i + 1 < n) {
                num[j][i + 1] += (num[j][i] - 1);
                ans += num[j][i] - 1;
                num[j][i] = 1;
            }
        }
    }
    cout << ans << '\n';
}

