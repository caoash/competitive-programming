#include <bits/stdc++.h>
using namespace std;

int rand(int a, int b){
	return a + rand()%(b-a+1);
}

void gen(){
    int a = rand(-5, 5);  
    int b = rand(-5, 5);  
    int c = rand(-5, 5);  
    int x1 = rand(-5, 5);  
    int x2 = rand(-5, 5);  
    int y1 = rand(-5, 5);  
    int y2 = rand(-5, 5);  
    printf("%d %d %d\n", a, b, c);
    printf("%d %d\n", x1, x2);
    printf("%d %d\n", y1, y2);
}

int main(int argc, char* argv[]){
    srand(atoi(argv[1]));
    gen();	
}
