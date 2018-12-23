/*
 * Michael Cao USACO Template
 */
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
#define oo (1<<30)
#define ins insert
#define eps 1e-9
#define FOR(i,n) for(int i = 0; i < (n); i++)
#define MOD 1000000007
#define REV(a,n) reverse(begin(a),begin(a)+n)
#define SORT(a,n) sort(begin(a),begin(a)+n)
#define mp make_pair

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

ifstream fin("inter.in");
ofstream fout("inter.out");

int n, m;


int main() {
    //code goes here
    fin >> n >> m;
    int cnt[n+5];
    int ans[n+5];

    FOR(i,n){
        cnt[i] = ans[i] = 0;
    }

    FOR(i, m){
        int x,y;
        fin >> x >> y;
        x--;
        y--;
        cnt[max(x,y)]--;
        cnt[min(x,y)]++;
    }

    FOR(i,n){
        ans[i + cnt[i]] = i+1;
    }

    FOR(i,n){
        fout << ans[i] << " ";
    }

    return 0;
}

