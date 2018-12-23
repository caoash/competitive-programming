using namespace std;
#include <bits/stdc++.h>
#define rep(i,n) for(auto i=0; i<(n); i++)
#define mem(x,val) memset((x),(val),sizeof(x));
#define rite(x) freopen(x,"w",stdout);
#define read(x) freopen(x,"r",stdin);
#define all(x) x.begin(),x.end()
#define sz(x) ((int)x.size())
#define sqr(x) ((x)*(x))
#define pb push_back
#define clr clear()
#define inf (1<<30)
#define ins insert
#define eps 1e-9
#define FOR(i,n) for(int i = 0; i < (n); i++)
#define F0R(i,n) for(int i = 0; i <= (n); i++)
#define MOD 1000000007
#define REV(a,n) reverse(begin(a),begin(a)+n)
#define SORT(a,n) sort(begin(a),begin(a)+n)

typedef string st;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<st> vs;
typedef map<int,int> mii;
typedef map<st,int> msi;
typedef set<int> si;
typedef set<st> ss;
typedef pair<int,int> pii;
typedef vector<pii> vpii;
typedef pair<int, pair<int,int> > ppi;

ll n, S;

ll solve(ll k, ll y[], ll n){

    ll newN[n];

    F0R(i, n){
        newN[i] = y[i] + ((i+1) * k);
    }

    sort(newN, newN + n);

    ll ret = 0;
    FOR(i, k){
        ret += newN[i];
    }

    return ret;
}

int main() {
    //code goes here

    cin >> n >> S;

    ll a[n];
    FOR(i,n){
        ll x;
        cin >> x;
        a[i] = x;
    }

    ll lo = 0;
    ll hi = n;
    pii ans = make_pair(0,0);

    while(lo <= hi){
        int mid = (hi + lo)/2;
        if(solve(mid, a, n) <= S){
            lo = mid+1;
            ans.first = mid;
            ans.second = solve(mid, a, n);
        }
        else{
            hi = mid-1;
        }

    }

    cout << ans.first << " " << ans.second << endl;

    return 0;
}

