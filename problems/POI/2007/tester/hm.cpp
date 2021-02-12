#include <bits/stdc++.h> 
using namespace std;

typedef long long ll;

#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)

#define F first
#define S second

const int MX = 30005;

struct Node {
    int adj[2];
    bool leaf = false;
    int p = -1;
    int pch;
    int suf = -1;
    int dp[2];
    Node() {
        memset(dp, -1, sizeof(dp));
        memset(adj, -1, sizeof(adj));
        pch = -1;
    };
};

struct AhoCorasick {
    Node gr[MX]; 
    int col[MX];
    int pt;

    AhoCorasick() {
        pt = 1;
        memset(col, 0, sizeof(col));
    }

    void Add(string s) {
        int pos = 0;
        for (char c : s) {
            int g = (c - '0');
            if (gr[pos].adj[g] == -1) {
                gr[pos].adj[g] = pt;
                gr[pt].p = pos, gr[pt].pch = g;
                ++pt;
            }
            pos = gr[pos].adj[g];
        }
        gr[pos].leaf = true;
    }

    void Innit() {
        queue<int> bfs;
        bfs.push(0);
        while (!bfs.empty()) {
            int curr = bfs.front();
            bfs.pop();
            if (gr[curr].p != -1) gr[curr].leaf |= gr[gr[curr].p].leaf;
            int link = Get(curr);
            if (link != -1) gr[curr].leaf |= gr[link].leaf;
            FOR(i, 2) {
                if (gr[curr].adj[i] != -1) bfs.push(gr[curr].adj[i]);
            }
        }
    }

    int Get(int v) {
        if (gr[v].leaf) return gr[v].suf = -1;
        if (gr[v].suf == -1) {
            if (v == 0 || gr[v].p == 0) {
                gr[v].suf = 0;
            } else {
                int res = Go(Get(gr[v].p), gr[v].pch);
                gr[v].suf = res; 
            }
        }
        return gr[v].suf;
    }

    int Go(int v, int g) {
        if (gr[v].leaf) return gr[v].dp[g] = -1;
        if (gr[v].dp[g] == -1) {
            if (gr[v].adj[g] != -1) {
                gr[v].dp[g] = gr[v].adj[g];
            } else {
                gr[v].dp[g] = (v == 0 ? 0 : Go(Get(v), g));
            }
        } 
        return gr[v].dp[g];
    }

    bool dfs(int v) {
        if (gr[v].leaf) return false;
        vector<int> to; 
        FOR(i, 2) {
            int e = Go(v, i);
            if (e != -1) to.push_back(e);
        }
        col[v] = 1;
        bool good = false;
        for (auto e : to) {
            if (col[e] == 1) good = true;
            else if (col[e] != 2) good |= dfs(e);
        }
        col[v] = 2;
        return good;
    }

    bool HasCycle() {
        bool ans = false;
        FOR(i, pt) {
            if (col[i] == 0) {
                bool go = dfs(i);
                ans |= go;
            }
        }
        return ans;
    }
};

AhoCorasick ahh;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    FOR(i, n) {
        string s; cin >> s;
        ahh.Add(s);
    }
    ahh.Innit();
    bool ans = ahh.HasCycle();
    cout << (ans ? "TAK" : "NIE") << '\n';
}

