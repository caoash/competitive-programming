
#include <bits/stdc++.h>
using namespace std;

int rand(int a, int b) {
    return a + rand() % (b - a + 1);
}
int main(int argc, char* argv[]) {
    srand(atoi(argv[1]));
    int T = 10;
    cout << T << '\n';
    while (T--) {
        int n = rand(2, 300), m = rand(1, n), k = rand(1, n);
        printf("%d %d %d\n", n, m, k);
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
            printf("%d %d %d\n", perm[a], perm[b], rand(1,15));
        }
    }
}
