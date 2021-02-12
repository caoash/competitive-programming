#include <bits/stdc++.h>
using namespace std;

int rand(int a, int b){
	return a + rand()%(b-a+1);
}

void gen(){
    int n = rand(20, 30);  
    cout << n << '\n';
    for (int i = 0; i < n; i++) {
        int len = rand(2, 6);
        string ret = "";
        for (int j = 0; j < len; j++) {
            int x = rand(0, 1);
            if (x) ret += "0";
            else ret += "1";
        }
        cout << ret << '\n';
    }
}

int main(int argc, char* argv[]){
    srand(atoi(argv[1]));
    gen();	
}
