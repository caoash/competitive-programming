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
    int n = rand(2, 1000), q = rand(1, 5);
    cout << n << " " << q << '\n';
    FOR(i, n) cout << rand(1, n) << " ";
    cout << '\n';
    FOR(i, q) {
        int l = rand(1, n - 1), r = rand(l, n);
        cout << l << " " << r << '\n';
    }
}

int main(int argc, char* argv[]){
    srand(atoi(argv[1]));
    gen();	
}

