#include <bits/stdc++.h>
using namespace std;

int rand(int a, int b){
    return a + rand()%(b-a+1);
}

const int MXV = 105;
const int MXM = 10;
const int MXQ = 1000;

void gen(){
    int q = MXQ;  
    cout << q << '\n';
    cout << 1 << " " << rand(-MXV, MXV) << '\n';
    int added = 1;
    for (int i = 0; i < q - 1; i++) {
        int qt = rand(1,3);
        cout << qt << ' ';
        if (qt == 1) {
            int v = rand(-MXV, MXV); 
            cout << v << '\n';
            ++added;
        } else if (qt == 2) {
            int ind = rand(1, min(MXM, added));
            int v = rand(-MXV, MXV);
            cout << ind << " " << v << '\n';
        } else {
            int ind = rand(1, MXM); 
            cout << ind << '\n';
        }
    }
}

int main(int argc, char* argv[]){
    srand(atoi(argv[1]));
    gen();	
}

