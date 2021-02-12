#include <bits/stdc++.h>
using namespace std;

int rand(int a, int b){
	return a + rand()%(b-a+1);
}

void gen(){
    int n = rand(1, 10);
    int l = rand(-10, 10), r = rand(l, 10), y = rand(1, 10);
    cout << n << '\n';
    cout << l << " " << r << " " << y << '\n';
    for (int i = 0; i < n; i++) {
        int x = rand(l, r);
        int v = rand(1, 10), h = rand(1, 10);
        cout << x << " " << v << " " << h << '\n';
    }
}

int main(int argc, char* argv[]){
    srand(atoi(argv[1]));
    gen();	
}
