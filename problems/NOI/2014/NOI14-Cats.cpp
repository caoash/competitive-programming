/*
Run some brute force and figure out the pattern after staring at output for a very long time.
*/

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

void solve(int X, int L, int N){
    int cnt = X;
    vi s1, s2;
    int b = 0;
    s1.pb(0);
    while (cnt > 0) {
        s2.pb(s1.back());
        s1.pop_back();
        if (s1.empty()) {
            s1.pb(b);
        }
        for (int i = 0; i < sz(s1); i++) {
            s1[i] = s1[i] ^ 1;
        }
        b ^= 1;
        if (s2.back() > L) {
            cnt--;
            if (cnt == 0) {
                cout << s2.back() << '\n';
                return;
            }
        }
        else {
            s2[sz(s2) - 1] += 2 * N;
            s1.pb(s2[sz(s2) - 1]);
            s1.pb(s2[sz(s2) - 1]);
            if(!s2.empty()) s2.pop_back();
            if(!s2.empty()) s2.pop_back();
        }
    }
}

void solveSmart(ll X, ll L, ll N) {
    X--;
    if (L / (2 * N) + 2 <= 62) X %= (1LL << (L / (2 * N) + 2));
    cout << 2 * N * (L / (2 * N) + 1) + __builtin_popcountll(X) % 2 << '\n';
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int Q; cin >> Q;
    while (Q--) {
        ll X, L, N; cin >> X >> L >> N;
        solveSmart(X, L, N);
    }
}