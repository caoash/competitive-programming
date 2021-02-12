#include <bits/stdc++.h> 
using namespace std;

typedef long long ll;

#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)

#define F first
#define S second

int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    vector<int> fib(n + 1);
    fib[1] = 1;
    fib[2] = 1;
    F0R(i, 3, n + 1) fib[i] = fib[i - 1] + fib[i - 2];
    vector<int> sum(n + 1);
    F0R(i, 1, n + 1) sum[i] = sum[i - 1] + fib[i];
    cout << sum[n] << '\n';
}

