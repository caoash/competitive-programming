/*
 * Template
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
#define REV(a,n) reverse(a,a+n)
#define SORT(a,n) sort(a,a+n)

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

#define mx 0

ifstream fin("panouri.in");
ofstream fout("panouri.out");

bool flag;
int n, t, c, ret;

int main() {
    //code goes here
    fin >> n >> t;
    int x[n+5], y[t+5];
    int cnt[20005];
    bool boards[20005];

    FOR(i,n){
        x[i] = 0;
    }

    FOR(i,t){
        y[i] = 0;
    }

    FOR(i, 20005){
        cnt[i] = 0;
        boards[i] = false;
    }


    FOR(i,n){
        fin >> x[i];
    }

    FOR(i,t){
        fin >> y[i];
        boards[y[i]] = true;
    }

    int p1 = 0;
    int p2 = 0;
    ret = oo;

    cnt[x[0]]++;
    if(boards[x[0]]) c++;

    flag = (t == 1 && (p1 == y[0] || p2 == y[0]));

    while(p1 < n && p2 < n && p2 >= p1){
        if(flag){
            if(boards[x[p1]]){
                cnt[x[p1]]--;
                if(cnt[x[p1]] == 0){
                     c--;
                }
            }
            p1++;
        }
        else{
            p2++;
            if(p2 == n){
                continue;
            }
            if(boards[x[p2]]){

                if(cnt[x[p2]] == 0){
                    c++;
                }
                cnt[x[p2]]++;
            }
        }
       if(c == t){
        ret = min(ret, p2-p1);
        flag = true;
       }
       else{
        flag = false;
       }

    }

    fout << (ret == oo ? -1 : ret) << endl;

    return 0;


}




