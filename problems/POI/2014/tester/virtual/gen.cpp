#include <bits/stdc++.h>
using namespace std;

int rand(int a, int b){
	return a + rand()%(b-a+1);
}

void gen(){
    int n = rand(2, 10), q = rand(1, 5);  
    cout << n << '\n';
    for (int i = 0; i < n; i++) cout << rand(1, 10) << " ";
    cout << '\n';
    cout << q << '\n';
    for (int i = 0; i < q; i++) cout << rand(1, n - 1) << '\n';
}

int main(int argc, char* argv[]){
    srand(atoi(argv[1]));
    gen();	
}
