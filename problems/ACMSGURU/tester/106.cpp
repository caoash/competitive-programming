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
const double EPS = 1e-6;

// -(a/b)x - (c/b)

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int a, b, c, x1, x2, y1, y2;
    cin >> a >> b >> c >> x1 >> x2 >> y1 >> y2;
    if (b == 0) {
        ll ans = 0;
        for (int cx = x1; cx <= x2; cx++) {
            ll comp = a * cx + c;
            if (comp == 0) ans += (y2 - y1 + 1);
        }
        cout << ans << '\n';
    } else {
        double m = -((double)a / (double)b);
        double yi = -((double)c / (double)b);
        auto f = [&] (double x) {
            return m * x + yi;
        };
        int ans = 0;
        bool found = false;
        for (double cx = x1; cx <= x2; cx++) {
            double comp = f(cx);
            if ((comp - floor(comp)) <= EPS || ceil(comp) - comp <= EPS) {
                int cc = (int) floor(comp);
                if(cc >= y1 && cc <= y2) {
                    ++ans;
                    found = true;
                }
            }
        }
        cout << ans << '\n';
    }
}

