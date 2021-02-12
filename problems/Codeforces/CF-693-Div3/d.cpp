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
    FOR(i, n) cin >> a[i];
    sort(a.begin(), a.end());
    reverse(a.begin(), a.end());
    bool turn = true;
    ll ascore = 0, bscore = 0;
    FOR(i, n) {
        if (turn) {
            if (a[i] % 2 == 0) ascore += a[i];
        } else {
            if (a[i] % 2 == 1) bscore += a[i];
        }
        turn = !turn;
    }
    if (ascore > bscore) cout << "Alice\n";
    else if (bscore > ascore) cout << "Bob\n";
    else cout << "Tie\n";
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

