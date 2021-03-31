#include <bits/stdc++.h> 
using namespace std;
 
typedef long long ll;
 
#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)
 
#define F first
#define S second

int rand(int a, int b){
    return a + rand()%(b-a+1);
}

void gen(){
    cout << 1 << '\n';  
    int n = rand(1, 105), m = rand(0, 8);
    cout << n << " " << m << '\n';
    vector<int> vals(8);
    FOR(i, 8) vals[i] = i + 2;
    random_shuffle(vals.begin(), vals.end());
    vector<int> res;
    FOR(i, m) res.push_back(vals[i]);
    sort(res.begin(), res.end());
    FOR(i, m) cout << res[i] << " ";
    cout << '\n';
}

int main(int argc, char* argv[]){
    srand(atoi(argv[1]));
    gen();	
}

