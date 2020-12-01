/*
K-th similar to POI17 Sum. 

Do dp[i][j][2] = length i, first element j, next element going down / up. Length 1 has exactly one of each, and then there's a 
bijection between length n - 1 and length n. See editorial for more info.
*/

#include <bits/stdc++.h> 
using namespace std;

using ll = long long;

using vi = vector<int>;
#define pb push_back
#define rsz resize
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using pi = pair<int,int>;
#define f first
#define s second
#define mp make_pair

ll dp[21][21][2];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int k; cin >> k;
    for (int i = 1; i < 21; i++) {
        for (int j = 1; j <= i; j++) {
            if (i == 1) {
                dp[i][j][0] = dp[i][j][1] = 1;
            } 
            else {
                dp[i][j][0] = 0;
                for (int k = 1; k < j; k++) {
                    dp[i][j][0] += dp[i - 1][k][1];
                }
                dp[i][j][1] = 0;
                for (int k = j + 1; k <= i; k++) {
                    dp[i][j][1] += dp[i - 1][k - 1][0];
                }
            }
        }
    }
    vi res;
    while (k--) {
        int n; ll c; cin >> n >> c;
        bool inc = false;
        for (int i = 1; i <= n; i++) {
            if (c > dp[n][i][0] + dp[n][i][1]) {
                c -= dp[n][i][0] + dp[n][i][1]; 
                continue;
            } 
            res.pb(i);
            if (c > dp[n][i][0]) {
                c -= dp[n][i][0];
                inc = true;
            }
            n--;
            break;
        }
        while (n > 0) {
            if (inc) {
                for (int i = res.back(); i <= n; i++) {
                    if (c > dp[n][i][0]) {
                        c -= dp[n][i][0];
                        continue;
                    }
                    res.pb(i);
                    break;
                }
            }
            else {
                for (int i = 1; i < res.back(); i++) {
                    if (c > dp[n][i][1]) {
                        c -= dp[n][i][1];
                        continue;
                    }
                    res.pb(i);
                    break;
                }
            }
            n--;
            inc = !inc;
        }
        set<int> vals;
        for (int x : res) {
            for (int x2 : vals) {
                if (x2 <= x){
                    x++;
                }
            }
            cout << x << " ";
            vals.insert(x);
        }
        cout << "\n";
        res.clear();
    }
}