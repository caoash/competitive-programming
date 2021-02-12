#include <bits/stdc++.h> 
using namespace std;

typedef long long ll;

#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)

#define F first
#define S second

const int MX = 1000005;

struct Trie {
    int adj[MX][61];
    int ptr = 1;

    void clear() {
        memset(adj, -1, sizeof(adj));
        ptr = 1;
    };

    int mp(char c) {
        if (c >= '0' && c <= '9') return c - '0';
        else if (c >= 'a' && c <= 'z') return 9 + (c - 'a');
        else return 35 + (c - 'A');
    }

    void add(string s) {
        int node = 0;
        FOR(ind, s.size()) {
            if (adj[node][mp(s[ind])] == -1) {
                node = adj[node][mp(s[ind])] = ptr;
                ++ptr;
            } else {
                node = adj[node][mp(s[ind])];
            }
        }
    }

    int dfs(int node) {
        int ans = 1;
        for (int to = 0; to < 61; to++) {
            if (adj[node][to] != -1) ans += dfs(adj[node][to]);
        }
        return ans;
    }

    int get_size() {
        return dfs(0);
    };
};

Trie tr;

int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    FOR(i, n) {
        string s; cin >> s;
        tr.clear();
        tr.add(s);
        while (s.size()) {
            s.erase(s.begin());
            tr.add(s);
        }
        cout << tr.get_size() << '\n';
    }
}

