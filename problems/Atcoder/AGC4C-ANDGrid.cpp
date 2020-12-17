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

const int MX = 505;
const int MOD = (int) (1e9 + 7);
const ll INF = (ll) 1e18;

bool blue[MX][MX], red[MX][MX];

int main(){
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int H, W; cin >> H >> W;
    for (int i = 0; i < H; i++) {
        blue[i][0] = true;
        red[i][W - 1] = true;
    }
    for (int i = 0; i < H; i++) {
        for (int j = 1; j < W - 1; j++) {
            if (i % 2) red[i][j] = true;
            else blue[i][j] = true;
        }
    }
    for (int i = 0; i < H; i++) {
        string s; cin >> s;
        for (int j = 0; j < W; j++) {
            if (s[j] == '#') red[i][j] = true, blue[i][j] = true; 
        }
    }
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            cout << (red[i][j] ? '#' : '.');    
        }
        cout << '\n';
    }
    cout << '\n';
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            cout << (blue[i][j] ? '#' : '.');    
        }
        cout << '\n';
    }
}

