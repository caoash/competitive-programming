/*
Given a fixed permutation, the optimal strategy clearly would be to go with the first person until its requirement is met, then the second, etc.

Now the question because, how do you generate the optimal permutation. Given two people, A and B, let's argue that A comes before B if A requires less
length to satisfy. The proof seems quite hard, maybe you can make some exchange arguments, I don't really know.

To deal with large fractions, use __int128.
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
 
struct fr{
    __int128 x, y;
    
    fr(__int128 X = 0, __int128 Y = 1){
        x = X, y = Y;
        ll g = __gcd(x, y);
        x /= g, y /= g;
    }
    
    friend fr operator+(fr a, fr b){
        return fr(a.x * b.y + b.x * a.y, a.y * b.y);
    }
    
    friend fr operator-(fr a, fr b){
        return fr(a.x * b.y - b.x * a.y, a.y * b.y);
    }
    
    friend fr operator*(fr a, fr b){
        return fr(a.x * b.x, a.y * b.y);
    }
    
    friend fr operator/(fr a, fr b){
        return fr(a.x * b.y, a.y * b.x);
    }
    
    friend bool operator<(fr a, fr b){
        return a.x * b.y < b.x * a.y;
    }
};
 
const int MX = 2005;
 
bool used[MX]; fr V[MX][MX]; fr nd[MX], dist[MX], ans[MX]; int ind[MX];
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N, L; cin >> N >> L;
    for (int i = 1; i <= N; i++) {
        V[i][0] = fr(0);
        for (int j = 1; j <= L; j++) {
            ll x; cin >> x; 
            V[i][j] = fr(x);
            if (j != 0) V[i][j] = V[i][j] + V[i][j - 1];
        }
    }
    nd[0] = fr(0);
    for (int i = 1; i <= N; i++) {
        ans[i] = fr(L + 1);
        for (int j = 1; j <= N; j++) {
            if (used[j]) {
                continue;
            }
            fr need = V[j][L] * fr(i, N);
            int it = lower_bound(V[j], V[j] + L, need) - V[j] - 1;
            fr to_add = fr(it) + (need - V[j][it]) / (V[j][it + 1] - V[j][it]);
            if (to_add < ans[i]) {
                ans[i] = to_add;
                ind[i] = j;
            }
        }
        if(i < N) cout << (ll) ans[i].x << " " << (ll) ans[i].y << '\n';
        used[ind[i]] = true;
    }
    for (int i = 1; i <= N; i++) {
        cout << ind[i] << " ";
    }
    cout << '\n';
}
