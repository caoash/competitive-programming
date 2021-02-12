#include <bits/stdc++.h> 
using namespace std;

typedef long long ll;

#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)

#define F first
#define S second

const int MX = 3000005;

int n;
vector<int> adj[MX];
int sub[MX];
int count_sub[MX];
bool works[MX];
int groups = 0;
vector<int> res;
vector<int> ord;

void bfs(int st) {
    queue<int> bfs;
    bfs.push(st);
    while (!bfs.empty()) {
        int v = bfs.front();
        bfs.pop();
        ord.push_back(v);
        for (int to : adj[v]) {
            bfs.push(to);
        }
    }
    reverse(ord.begin(), ord.end());
    for (auto v : ord) {
        sub[v] = 1;
        for (int to : adj[v]) {
            sub[v] += sub[to];
        }
        count_sub[sub[v]]++;
    }
}

void go(int len) {
    for (int l = 0; len * l <= n; ++l) {
        groups += count_sub[l * len];
    }
}

bool Tri(int len) {
    groups = 0;
    go(len);
    if (groups == (n / len)) {
        return true;
    }
    return false;
}

int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    FOR(i, n - 1) {
        int p; cin >> p;
        adj[p - 1].push_back(i + 1);
    }
    bfs(0);
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            if (Tri(i)) works[n / i] = true;
            if (i != (n / i)) {
                if (n % (n / i) == 0) {
                    if (Tri(n / i)) works[i] = true;
                }
            }        
        } 
    }
    F0R(i, 1, n + 1) if (works[i]) cout << i << " ";
    cout << '\n';
}

