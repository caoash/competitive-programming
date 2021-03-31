#include "bits/stdc++.h"
 
using namespace std;
 
//sad; long long double doesn't exist
using ld = long double;
 
//imagine a language where int = long
#define long long long
 
//typing too hard
#define endl "\n"
 
#define sz(x) int((x).size())
 
const int maxn = 1e6, buff = 2e5, n = maxn + buff;
 
int m;
long bit[n + 1];
 
//init
void inicjuj(int _n) {
    m = 0;
}
 
void add(int ind, long x) {
    ind++;
    while(ind <= n) {
        bit[ind] += x;
        ind += ind & -ind;
    }
}
 
long psum(int ind) {
    long ans = 0;
    while(ind > 0) {
        ans += bit[ind];
        ind -= ind & -ind;
    }
    return ans;
}
 
long sum(int l, int r) {
    return psum(r + 1) - psum(l);
}
 
//append
void dodaj(int x) {
    add(m++, x);
    if(m == n) {
        for(int i = 0; i < maxn; i++) {
            add(i, -sum(i, i) + sum(i + buff, i + buff));
        }
        for(int i = maxn; i < n; i++) {
            add(i, -sum(i, i));
        }
        m = maxn;
    }
}
 
//set
void koryguj(int ind, int x) {
    add(m - ind, x);
}
 
//x
long suma(int ind) {
    return sum(m - ind, m - 1);
}
 
int main() {
    cin.tie(0)->sync_with_stdio(0);
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int type; cin >> type;
        if(type == 1) {
            int x;
            cin >> x;
            dodaj(x);
        }else if(type == 2) {
            int ind, x;
            cin >> ind >> x;
            koryguj(ind, x);
        }else if(type == 3) {
            int ind;
            cin >> ind;
            long ans = suma(ind);
            cout << ans << endl;
        }
    }
}
 
