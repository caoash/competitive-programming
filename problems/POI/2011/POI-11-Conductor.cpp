#include <bits/stdc++.h> 
using namespace std;

using ll = long long;

using vi = vector<int>;
using vl = vector<ll>;
#define pb push_back
#define rsz resize
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using pi = pair<int,int>;
#define f first
#define s second
#define mp make_pair

const int MX = 500005;
const int MOD = (int) (1e9 + 7);
const ll INF = (ll) 1e18;

int main(){
    cin.tie(0);
	ios::sync_with_stdio(0);
    int n;
    cin >> n;
    vi a(n);
    vi pre(n), suf(n);
	for(int i = 0 ; i < n; ++i) {
        cin >> a[i];
    }
    int m = -1;
    for (int i = n - 1; i >= 0; --i) {
        if (a[i] <= m) {
            continue;
        }
        m = a[i];
        int j, k, c;
        for (j = i - 1, k = 1, c = 1; j >= 0; j -= k, k += 2, ++c) {
            suf[j] = max(suf[j], a[i] + c);
        }
    }
    m = -1;
    for (int i = 0; i < n; ++i) {
        if (a[i] <= m) {
            continue;
        }
        m = a[i];
        int j, k, c;
        for (j = i + 1, k = 1, c = 1; j < n; j += k, k += 2, ++c) {
            pre[j] = max(pre[j], a[i] + c);
        }
    }
    for (int i = 1; i < n; ++i) {
        pre[i] = max(pre[i - 1], pre[i]);
    }
    for (int i = n - 2; i >= 0; --i) {
        suf[i] = max(suf[i + 1], suf[i]);
    }
    for (int i = 0; i < n; ++i) {
        cout << max(0, max(suf[i], pre[i]) - a[i]) << '\n';     
    }
}

