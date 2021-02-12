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

char grid[1000][1000];

int main(){
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int siz = 31;
    // int siz = 11;
    int len = 323;
    // int len = 11;
    for (int i = 0; i < len; i++) {
        string s; cin >> s;
        cout << s << '\n';
        for (int j = 0; j < siz; j++) grid[i][j] = s[j];
    }
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < siz; j++) {
            cout << grid[i][j] << " ";
        }
        cout << '\n';
    }
    int pos_x = 0, pos_y = 0;
    int ans = 0;
    cout << siz << '\n';
    int ma = 1, mb = 2;
    while (pos_y < len) {
        cout << pos_x << " " << pos_y << " " << grid[pos_y][pos_x] << endl;
        if (grid[pos_y][pos_x] == '#') ++ans;
        pos_x += ma;
        pos_y += mb;
        pos_x %= siz;
    }
    cout << ans << '\n';
}

