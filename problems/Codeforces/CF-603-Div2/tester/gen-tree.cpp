
#include <bits/stdc++.h>
using namespace std;

int rand(int a, int b) {
    return a + rand() % (b - a + 1);
}

const int MX = 1005;

int anc[MX];
vector<int> adj[MX][2];
vector<int> stor;

void dfs(int v, int p) {
    if (adj[v][0].size() == 1) {
        stor.push_back(v);
    }
    for (int to : adj[v][0]) {
        if (to != p) {
            anc[to] = v;
            dfs(to, v);
        }
    }
}

int main(int argc, char* argv[]) {
    srand(atoi(argv[1]));
    int a = rand(2, 15);
    vector<pair<int,int>> edges;
    for(int i = 2; i <= a; ++i) {
        edges.emplace_back(rand(1, i - 1), i);
    }
    
    vector<int> perm(a + 1); // re-naming vertices
    for(int i = 1; i <= a; ++i) {
        perm[i] = i;
    }
    random_shuffle(perm.begin() + 1, perm.end());
    
    random_shuffle(edges.begin(), edges.end()); // random order of edges
    
    for(pair<int, int> edge : edges) {
        int u = edge.first, v = edge.second;
        adj[perm[u]][0].push_back(perm[v]);
        adj[perm[v]][0].push_back(perm[u]);
    }
    dfs(1, -1);
    cout << stor.size() << '\n';
    cout << a << '\n';
    for (int i = 2; i <= a; i++) cout << anc[i] << " ";
    cout << '\n';
    for (int i = 0; i < stor.size(); i++) cout << stor[i] << " ";
    cout << '\n';
    cout << a << '\n';
    reverse(stor.begin(), stor.end());
    for (int i = 2; i <= a; i++) cout << anc[i] << " ";
    cout << '\n';
    for (int i = 0; i < stor.size(); i++) cout << stor[i] << " ";
}
