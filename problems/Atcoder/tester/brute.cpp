#include<bits/stdc++.h>
 
 
#define ll long long
#define rep(A,B,C) for(A=B;A<C;++A)
#define nrep(A, B, C) for (A = C - 1;A >= B;--A)
#define pii pair<int,int>
#define pll pair<ll,ll>
#define vv vector
 
#define fi first
#define se second
#define all(A) A.begin(),A.end()
 
using namespace std;
 
/////////////////////////////////////////////////////
//#define MOD 998244353
 
ll T;
ll i, j, k;
 
 
void calc(const vv<ll>& A,ll& ran,ll& rbn,ll& rblast){
    ll i;
    ll bn=0, an=0, blast = 0;
    rep(i,0,A.size()){
        if(A[i]==0)
            ++an;
        else
            ++bn;
    }
    nrep(i,0,A.size()){
        if(A[i]!=1)
            break;
        ++blast;
    }
    rbn = bn, ran = an, rblast = blast;
}
string outsolve(const vv<ll>& bav){
    ll i, j;
    string ret;
    rep(i,0,bav.size()){
        rep(j,0,bav[i]){
            if(i%2==0)
                ret += 'b';
            else
                ret += 'a';
        }
    }
    return ret;
}
 
void solve(){
    string S;
    cin >> S;
 
    if(S.size()<=2){
        cout << S << endl;
        return;
    }
 
    vv<ll> A;
    rep(i,0,S.size()){
        A.push_back(S[i] == 'a' ? 0 : 1);
    }
 
    ll N = A.size();
    ll an = 0, bn = 0, blast = 0;
    calc(A, an, bn, blast);
    /*
    rep(i,0,N){
        printf("%lld", A[i]);
    }
    printf("\n");
    */
    if(an==N||bn==N){
        cout << S << endl;
        return;
    }
 
    if (blast > 0)
    {
        N -= blast;
        if(an%2==0){
            cout << outsolve({bn}) << endl;
            return;
        }
        if (blast < 3)
        {
            cout << outsolve({bn - blast, 1, blast})<<endl;
            return;
        }
 
        if (blast == bn)
        {
            cout << outsolve({0, 1, bn})<<endl;
            return;
        }
 
        if(A[0]==0&&A[1]==0){
            ll an = 0;
            rep(i,0,N){
                if(A[i]!=0)
                    break;
            }
            rep(i,i,N){
                if (A[i] == 0 && A[i + 1] == 0)
                    break;
            }
            if(i==N)
                --i;
            A[0] = A[i] = 2;
            reverse(A.begin() + 1, A.begin() + i);
        }
    }else{
        if(A[0]==0&&A[1]==0){
            nrep(i,0,N){
                if(A[i]!=0)
                    break;
            }
            ++i;
            A[1] = A[i] = 2;
            reverse(A.begin(), A.begin() + i + 1);
        }
    }
    /*
    rep(i,0,A.size()){
        printf("%lld", A[i]);
    }
    printf("\n");
    */
 
    vv<ll> B;
    an = 0;
    j = -1;
    
    rep(i,0,A.size()){
        if(A[i]==0){
            ++an;
        }
        if(A[i]==1){
            if(an==1){
                if(j==-1){
                    j = i;
                }else{
                    A[j - 1] = A[i - 1] = 2;
                    reverse(A.begin() + j, A.begin() + i - 1);
                    j = -1;
                }
            }
            an = 0;
        }
    }
    /*
    rep(i,0,A.size()){
        printf("%lld", A[i]);
    }
    printf("\n");
    */
 
    A.push_back(1);
    an = 0;
    rep(i,0,A.size()){
        if(A[i]==0)
            ++an;
        if(A[i]==1){
            if(an>0)
                B.push_back(an);
            an = 0;
        }
    }
    if(B.size()!=0)
        an = B[0];
    rep(i,1,B.size()){
        an += B[i];
        an -= 2;
    }
    
 
    if (blast > 0)
    {
        bn -= 2;
    }
    
    cout << outsolve({bn, an}) << endl;
}
 
 
int main()
{
    scanf("%lld", &T);
    while(T--){
        solve();
    }
    return 0;
}
