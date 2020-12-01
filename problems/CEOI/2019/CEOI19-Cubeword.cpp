/*
 * So if you consider the cube as a bipartite graph, the problem reduces to count the number of ways to fill in the edges.
 *
 * Let's fix the left side of the graph. Then for some fixed vertex, we just need the number of ways to fill the three vertices on the right it connects to.
 *
 * Let num[a][b][c] = number of strings that start with a, b, c and end with any letter. Then if we fix our left side to be A, B, C, D, the number of ways to fill
 * the right side is num[A][B][C] * num[A][B][D] * num[B][C][D] * num[A][C][D] since those are the edges that connect to the right side. 
 *
 * To speed it up, only consider A <= B <= C <= D and a < b < c and do a bit of math to deal with undercounting.
 */

#pragma GCC optimize ("Ofast")
#pragma GCC target ("avx2")
 
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
const int MOD = (int) 998244353;
const ll INF = (ll) 1e18;
const int ALPH = 63;
 
int n;
vector<string> words[11];
ll ways[ALPH][ALPH][ALPH];
int occ[ALPH][ALPH];
 
int getc(char c) {
    if (c <= '9') return c - '0';
    else if (c <= 'Z') return 10 + (c - 'A');
    else if (c <= 'z') return 36 + (c - 'a');
    else return -1;
}
 
char rev(int x) {
    if (x <= 9) return x + '0';
    else if (x <= 35) return (x - 10) + 'A';
    else return (x - 36) + 'a';
}
 
 
ll solve(int len) {
    memset(ways, 0, sizeof(ways));
    memset(occ, 0, sizeof(occ));
    vector<string> curr = words[len];
    for (auto x : curr) {
        occ[getc(x[0])][getc(x[sz(x) - 1])]++;
    }
    for (int i = 0; i < ALPH; i++) {
        for (int j = i; j < ALPH; j++) {
            for (int k = j; k < ALPH; k++) {
                for (int l = 0; l < ALPH; l++) {
                    ways[i][j][k] += (((occ[i][l] * occ[j][l]) % MOD) * occ[k][l]) % MOD;
                    ways[i][j][k] %= MOD;
                }
            }
        }
    }
    auto sv = [&] (int i, int j, int k, int l) {
        if (i > j) swap(i, j);
        if (j > k) swap(j, k);
        if (k > l) swap(k, l);
        if (i > j) swap(i, j);
        if (j > k) swap(j, k);
        if (i > j) swap(i, j);
        return ((((((ways[i][j][k] * ways[i][j][l]) % MOD) * ways[i][k][l]) % MOD) * ways[j][k][l]) % MOD);
    };
    ll ret = 0;
    for (int i = 0; i < ALPH; i++) {
        for (int j = i; j < ALPH; j++) {
            for (int k = j; k < ALPH; k++) {
                if (ways[i][j][k] == 0) continue;
                for (int l = k; l < ALPH; l++) {
                    if (ways[i][j][l] == 0 || ways[i][k][l] == 0 || ways[j][k][l] == 0) continue;
                    ll cv = sv(i, j, k, l);
                    int prms = 24; 
                    if (i == j && j == k && k == l) prms /= 24;
                    else if (i == j && j == k) prms /= 6;
                    else if (j == k && k == l) prms /= 6;
                    else {
                        int rem = 2 * ((i == j) + (i == k) + (i == l) + (j == k) + (j == l) + (k == l));
                        if (rem != 0) prms /= rem;
                    }
                    ret += (cv * prms) % MOD;
                    ret %= MOD;
                }
            }
        }
    }
    return ret;
}
 
int main(){
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    set<int> lens;
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        string c; cin >> c;
        words[sz(c)].pb(c);
        reverse(all(c));
        words[sz(c)].pb(c);
        lens.insert(sz(c));
    }
    for (int l = 0; l < 11; l++) {
        sort(all(words[l]));
        words[l].erase(unique(all(words[l])), words[l].end());
    }
    for (auto x : lens) ans += solve(x), ans %= MOD;
    cout << ans << '\n';
}
