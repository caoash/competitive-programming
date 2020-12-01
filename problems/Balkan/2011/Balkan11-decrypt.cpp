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

void solve(int n, int a, int b, int c) {
    vi val(n);
    cout << "GO: " << n << " " << a << " " << b << " " << c;
    val[0] = a, val[1] = b, val[2] = c;
    for (int i = 3; i < n; i++) {
        val[i] = val[i - 2] ^ val[i - 3];
    }
    for (int i = 0; i < n; i++) {
        if (i % 7 == 0) cout << '\n';
        cout << val[i] << " ";
    }
    cout << '\n';
    cout << '\n';
}

int main() {
    for (int i = 1; i <= 100; i++) {
        for (int j = 1; j <= 100; j++) {
            for (int k = 1; k <= 100; k++) {
                solve(21, i, j, k);
            }
        }
    }
}

