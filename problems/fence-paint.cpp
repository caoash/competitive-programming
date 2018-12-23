/*
 * Michael Cao USACO Template
 */

#include <bits/stdc++.h>
using namespace std;

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
#define MOD 1000000007
#define REV(a,n) reverse(begin(a),begin(a)+n)
#define SORT(a,n) sort(begin(a),begin(a)+n)

typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<string> vs;
typedef map<int,int> mii;
typedef map<string,int> msi;
typedef set<int> si;
typedef set<string> ss;
typedef pair<int,int> pii;
typedef vector<pii> vpii;



ifstream f("paint.in"); // u can use anything, not just f and g
ofstream g("paint.out");

int main() {
    int a, b, c, d;
    //code goes here
    f >> a >> b >> c >> d;

    int n1 = max(b,d); //larger of b or d
    int n2 = min(b,d); //smaller of b or d
    int n3 = n1 == b ? a : c; //pair with n1
    int n4 = n2 == b ? a : c; //pair with n2

    if(n3 <= n2){
        if(n3 <= n4){
            g << n1 - n3 << endl;
        }
        else{
            g << n1 - n4 << endl;
        }
    }
    else if(n3 > n2){
        g << (n1 - n3) + (n2 - n4);
    }

    return 0;
}

