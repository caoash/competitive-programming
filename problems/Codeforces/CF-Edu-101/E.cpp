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
    int n, k; cin >> n >> k;
    string s; cin >> s;
    vector<int> one(n);
    FOR(i, n) {
        if (s[i] == '0') s[i] = '1';
        else s[i] = '0';
        one[i] = (!i ? 0 : one[i - 1]) + (s[i] == '1');
    }
    set<ll> has;
    FOR(i, n - k + 1) {
        ll val = 0;    
        int len = min(k, 20);
        F0R(j, i + k - len, i + k) {
            val *= 2; 
            val += (s[j] - '0');
        }
        bool good = true;
        if (i + k - len > i) {
            int z = one[i + k - len - 1] - (!i ? 0 : one[i - 1]);
            if (z) good = false;
        }
        if (good) {
            has.insert(val);
        }
    }
    int ans = (n - k + 1);
    FOR(i, ans) if (!has.count(i)) ans = min(ans, i);
    if (k > 22) {
        cout << "YES\n";
    } else if (ans < (1 << k)) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
        return;
    }
    string ret;
    while (ans) {
        ret += (ans % 2) + '0';
        ans /= 2;
    }
    while((int) ret.size() < k) ret += "0";
    reverse(ret.begin(), ret.end());
    cout << ret << '\n';
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

