#include <bits/stdc++.h> 
using namespace std;

typedef long long ll;

#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)

#define F first
#define S second

int sum[2];
int ops = 0;

void Query(int t, int x) {
    ++ops;
    if (t == 0) {
        cout << "EMPTY " << x << endl;
        sum[x - 1] = 0;
    } else if (t == 1) {
        cout << "PLACE " << x << endl;
        sum[x - 1]++;
    } else {
        cout << "DISCARD" << endl;
    }
}

int tcs = 0;

void Solve() {
    ++tcs;
    sum[0] = 0, sum[1] = 0;
    int A, B, C; cin >> A >> B >> C;
    int mn = min({A, B, C});
    array<int, 3> give;
    give[0] = 0, give[1] = 0, give[2] = 0;
    int bad = -1;
    FOR(i, 66) {
        char c; cin >> c;
        if (c == '-') {
            exit(0);
        }
        if (sum[0] + sum[1] >= 34) {
            Query(-1, -1);
            continue;
        }
        if (c == 'R') {
            Query(1, 1);
            give[0]++;
        } else if (c == 'G') {
            Query(1, 2);
            give[1]++;
        } else {
            Query(-1, -1);
            give[2]++;
        }
    }
    mn = 100;
    char c; cin >> c;
    if (c == '-') exit(0);
    if (c == 'R') give[0]++;
    else if (c == 'G') give[1]++;
    else give[2]++;
    FOR(i, 3) {
        if (give[i] < mn) mn = give[i], bad = i;
    }
    if (bad < 2) Query(0, bad + 1);
    else Query(-1, -1);
    FOR(i, 34) {
        cin >> c;
        if (c == '-') exit(0);
        if (sum[0] + sum[1] >= 34) {
            Query(-1, -1);
            continue;
        }
        if (c == 'R') {
            if (bad != 0) {
                Query(1, 1);
            } else {
                Query(-1, -1);
            }
        } else if (c == 'G') {
            if (bad != 1) {
                Query(1, 2);
            } else {
                Query(-1, -1);
            }
        } else {
            if (bad != 2) {
                if (bad == 0) Query(1, 1);
                else Query(1, 2);
            } else {
                Query(-1, -1);
            }
        }
    }
}

int main() {
    /*
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    */
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T; cin >> T;
    assert(T == 100);
    while (T--) {
        Solve();
    }
}

