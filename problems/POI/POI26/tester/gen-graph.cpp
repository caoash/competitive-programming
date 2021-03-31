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
    // int n = rand(10, 20), m = rand(2 * n, 40);  
    int n = rand(10, 20), m = rand(2 * n, 4 * n);
    int k = rand(1, n);
    cout << n << " " << m << " " << k << '\n';
    vector<int> vals(n);
    iota(vals.begin(), vals.end(), 1);
    random_shuffle(vals.begin(), vals.end());
    FOR(i, k) {
        cout << vals[i] << " ";
    }
    cout << '\n';
    vector<pair<int, int>> ed;
    set<pair<int, int>> things;
    F0R(i, 2, n + 1) {
        int p = rand(1, i - 1);
        int dir = rand(1, 2);
        if (dir == 2) ed.push_back(make_pair(p, i));
        else ed.push_back(make_pair(i, p));
        things.insert(make_pair(i, p));
        --m;
    }
    while (m > 0) {
        int u = rand(1, n - 1); 
        int v = rand(u + 1, n);
        int s = rand(1, 2);
        if (s == 2) swap(u, v);
        if (!things.count(make_pair(u, v))) {
            ed.push_back(make_pair(u, v));
            things.insert(make_pair(u, v));
            m--;
        }
    }
    for (auto x : ed) {
        cout << x.F << " " << x.S << '\n';
    }
}

int main(int argc, char* argv[]){
    srand(atoi(argv[1]));
    gen();	
}
