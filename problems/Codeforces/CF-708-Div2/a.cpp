#include <bits/stdc++.h> 
using namespace std;
 
typedef long long ll;
 
#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)
 
#define F first
#define S second

void Solve() {
    int n; cin >> n;
    vector<int> a(n);
    vector<int> cnt(101);
    FOR(i, n) {
        cin >> a[i];
        cnt[a[i]]++;
    }
    vector<int> b;
    FOR(i, 101) if (cnt[i] > 0) cnt[i]--, b.push_back(i);
    FOR(i, 101) {
        while(cnt[i] > 0) cnt[i]--, b.push_back(i);
    }
    for (auto x : b) cout << x << " ";
    cout << '\n';
}
 
int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);    
    int T; cin >> T;
    while (T--) {
        Solve();
    }
}

