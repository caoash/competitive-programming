
#include <bits/stdc++.h>
using namespace std;

int rand(int a, int b) {
    return a + rand() % (b - a + 1);
}
const int MX = 15;
int main(int argc, char* argv[]) {
    srand(atoi(argv[1]));
    int n = rand(2, MX);
    int s = rand(2, n);
    int k = rand(2, min(20, n)); 
    printf("%d %d %d\n", n, s, k);
    vector<pair<int,int>> edges;
    for(int i = 2; i <= n; ++i) {
        edges.emplace_back(rand(1, i - 1), i);
    }
    
    vector<int> perm(n + 1); // re-naming vertices
    for(int i = 1; i <= n; ++i) {
        perm[i] = i;
    }
    random_shuffle(perm.begin() + 1, perm.end());
    
    random_shuffle(edges.begin(), edges.end()); // random order of edges
    
    for(pair<int, int> edge : edges) {
        int a = edge.first, b = edge.second;
        if(rand() % 2) {
            swap(a, b); // random order of two vertices
        }
        cout << perm[a] << " " << perm[b] << '\n';
    }
}
