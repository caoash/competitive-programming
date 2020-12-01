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

void riprogramma(int N, int K, vi &C) {
    if (K == 2) {
        pi ans = mp(0, 0);
        for (int i = 0; i < N; i++) {
            if (i % 2) {
                ans.f += (C[i] > 1);
                ans.s += (C[i] == 1);
            } else {
                ans.f += (C[i] == 1);
                ans.s += (C[i] > 1);
            }
        }
        vi ret(N);
        if (ans.f > ans.s) {
            for (int i = 0; i < N; i++) C[i] = (i % 2) + 1;
        } else {
            for (int i = 0; i < N; i++) C[i] = ((i % 2) == 0) + 1;
        }
    } else {
        for (int i = 1; i < N; i++) {
            if (C[i] == C[i - 1]) {
                int rep = C[i - 1];
                rep = ((rep + 1) % K) + 1;
                if (i != N - 1 && rep == C[i + 1]) {
                    rep = ((rep + 1) % K) + 1;
                }
                C[i] = rep;
            }
        }
    }
}

/*
int main(){
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N, K; cin >> N >> K;
    vi dat;
    for (int i = 0; i < N; i++) {
        int ci; cin >> ci;
        dat.pb(ci);
    }
    riprogramma(N, K, dat);
}
*/

