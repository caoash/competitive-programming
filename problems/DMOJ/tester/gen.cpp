#include <bits/stdc++.h>
using namespace std;

int rand(int a, int b){
	return a + rand()%(b-a+1);
}

const int MAXN = 100;
const int MAXQ = 10;
const int MAXV = 100000000;

void gen(){
    int n = rand(1, MAXN), q = rand(MAXQ, MAXQ);  
    cout << n << " " << q << '\n';
    multiset<int> elems;
    for (int i = 0; i < n; i++) {
        int x = rand(1, MAXV);
        cout << x << " ";
        elems.insert(x);
    }
    cout << '\n';
    for (int i = 0; i < q; i++) {
        int qt = rand(1, 4);
        if (qt == 1) {
            cout << "I ";
            int v = rand(1, MAXV);
            elems.insert(v);
            cout << v << '\n';
        } else if (qt == 2) {
            cout << "R ";
            int v = rand(1, MAXV);
            if (elems.count(v)) elems.erase(elems.find(v));
            cout << v << '\n';
        } else if (qt == 3) {
            cout << "L ";
            cout << rand(1, MAXV) << '\n';
        } else if (qt == 4) {
            if (elems.empty()) {
                cout << "L ";
                cout << rand(1, MAXV) << '\n';
            }
            else {
                cout << "S ";
                cout << rand(1, elems.size()) << '\n';
            }
        }
    }
}

int main(int argc, char* argv[]){
    srand(atoi(argv[1]));
    gen();	
}
