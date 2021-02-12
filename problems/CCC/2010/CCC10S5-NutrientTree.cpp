#include <bits/stdc++.h> 
using namespace std;

typedef long long ll;

#define F0R(i, x, y) for (int i = x; i < y; i++)
#define FOR(i, n) F0R(i, 0, n)
#define F0RD(i, x, y) for (int i = y - 1; i >= x; i--)
#define FORD(i, n) F0RD(i, 0, n)

#define F first
#define S second

int anc[105], val[105];
int X;
int dp[105][2505], dp2[105][2505];
vector<int> adj[105];

void dfs(int v) {
    if (adj[v].size()) {
        assert(adj[v].size() == 2);
        FOR(i, 2) dfs(adj[v][i]);
        FOR(i, X + 1) FOR(j, X - i + 1) {
            if (i + j <= X) dp2[v][i + j] = max(dp2[v][i + j], dp[adj[v][0]][i] + dp[adj[v][1]][j]);
        }
        FOR(i, X + 1) FOR(j, X - i + 1) {
            if (i + j <= X) dp[v][i + j] = max(dp[v][i + j], min(dp2[v][i], (1 + j) * (1 + j)));
        }
    } else {
        FOR(i, X + 1) FOR(use, X - i + 1) {
            if (i + use <= X) {
                dp[v][i + use] = max(dp[v][i + use], min(val[v] + i, (1 + use) * (1 + use)));
                dp2[v][i + use] = max(dp2[v][i + use], val[v] + i);
            }
        }
    }
}

bool isNum(char c) {
    return (c >= '0' && c <= '9');
}

int main() {
#ifdef mikey 
    freopen("a.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    string line;
    getline(cin, line);
    int cnt = 0;
    stack<int> vals;
    memset(val, -1, sizeof(val));
    int pt = 0;
    while (pt < (int) (line.size())) {
        char c = line[pt];
        if (c == '(') vals.push(cnt++);
        else if (c == ')') {
            int cur = vals.top();
            vals.pop();
            int prev = (vals.empty() ? -1 : vals.top());
            if (prev != -1) adj[prev].push_back(cur);
        } else if (isNum(c)) {
            int num = 0;
            while (isNum(c) && pt < (int) (line.size())) {
                num = (num * 10) + (c - '0');
                ++pt;
                if (pt < (int) (line.size())) c = line[pt];
            }
            int prev = (vals.empty() ? -1 : vals.top());
            if (prev != -1) adj[prev].push_back(cnt);
            val[cnt] = num;
            ++cnt;
            --pt;
        }
        ++pt;
    }
// FOR(i, cnt) dbg(i, anc[i], val[i]);
    cin >> X;        
    dfs(0);
    cout << dp2[0][X] << '\n';
}

