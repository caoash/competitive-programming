#include <bits/stdc++.h> 
using namespace std;
 
typedef long long ll;
 
#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)
 
#define F first
#define S second

#include <bits/stdc++.h>
using namespace std;

int rand(int a, int b){
    return a + rand()%(b-a+1);
}

int main(int argc, char* argv[]){
    srand(atoi(argv[1]));
    string alph = "ab";
    int n = rand(1, 1);
    cout << n << '\n';
    for (int i = 0; i < n; i++) {
        string s = "";
        int len = rand(1, 100);
        for (int j = 0; j < len; j++) {
            int c = rand(0, 1); 
            s += alph[c];
        }
        cout << s << '\n';
    }
}
 
