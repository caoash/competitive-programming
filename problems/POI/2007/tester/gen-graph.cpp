
#include <bits/stdc++.h>
using namespace std;

int rand(int a, int b) {
    return a + rand() % (b - a + 1);
}
set<pair<int,int>> has;
int main(int argc, char* argv[]) {
    srand(atoi(argv[1]));
    int n = rand(5, 7); int m = n+1;
    cout << n << " " << m << "\n";
    vector<pair<int,int>> edges;
    for(int i = 2; i <= n; ++i) {
        edges.emplace_back(rand(1, i - 1), i);
    }
    
    vector<int> perm(n + 1); // re-naming vertices
    for(int i = 1; i <= n; ++i) {
		 has.insert({i,i});
       perm[i] = i;
    }
    random_shuffle(perm.begin() + 1, perm.end());
    random_shuffle(edges.begin(), edges.end()); // random order of edges
    vector<pair<int,int>> ret;
    for(pair<int, int> edge : edges) {
        int a = edge.first, b = edge.second;
        if(rand() % 2) {
            swap(a, b); // random order of two vertices
        }
        ret.push_back(make_pair(perm[a], perm[b]));
        has.insert({perm[a], perm[b]}); has.insert({perm[b], perm[a]});
    }
    for(int i = n; i <= m; i++){
		int a = rand(1,n); int b = rand(1,n);
		while(has.count(make_pair(a,b))){
			a = rand(1,n); b = rand(1,n);
		}
		ret.push_back(make_pair(a,b));
		has.insert({a,b}); has.insert({b,a});
	 }
	 for(pair<int,int> p : ret){
		 cout << p.first << " " << p.second << "\n";
	 }
}
