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

set<ll> cubes;

void solve() {
    ll x; cin >> x;
    for(ll i=1;i<=10000;i++){
        ll a=(i*i*i); 
        ll need=(x-a);
        if(cubes.count(need)){
            cout<<"YES\n";
            return;
        }
    }
    cout<<"NO\n";
    return;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    for(ll i=1;i<=10000;i++){
        cubes.insert(i*i*i);
    }
    while(t--){
        solve(); 
    }
}
