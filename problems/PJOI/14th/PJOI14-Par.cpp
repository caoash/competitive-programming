#include <bits/stdc++.h> 
using namespace std;

typedef long long ll;

#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)

#define F first
#define S second

string multiply(string num1, string num2) {
    vector<int> res(num1.size()+num2.size(),0);
    for(int i=num1.size()-1;i>=0;i--)
    {
        for(int j=num2.size()-1;j>=0;j--)
        {
            res[i+j+1]+=(num1[i]-'0')*(num2[j]-'0');
            res[i+j]+=res[i+j+1]/10;
            res[i+j+1]%=10;
        }
    }

    int start=0;
    while(start<res.size()&&res[start]==0)
        start++;
    if(start==res.size())
        return "0";

    string result="";
    for(int i=start;i<res.size();i++)
        result+=(res[i]+'0');
    return result;
}

int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll N; cin >> N;
    string res = "";
    while (N > 0) {
        res += ((N % 5) + '0');
        N /= 5;
    }
    reverse(res.begin(), res.end());
    cout << multiply(res, "2") << '\n';
}

