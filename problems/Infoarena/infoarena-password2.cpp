#include <bits/stdc++.h> 
using namespace std;

using ll = long long;

using vi = vector<int>;
using vl = vector<ll>;
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define lb lower_bound
#define ub upper_bound

using pi = pair<int,int>;
#define f first
#define s second
#define mp make_pair

const int MX = 200005;
const int MOD = (int) (1e9 + 7);
const ll INF = (ll) 1e18;

int n, m;
int cnt[26];
string alph = "abcdefghijklmnopqrstuvwxyz";

int query(string s) {
    cout << s << endl;
    int ret; cin >> ret;
    if (ret == n) {
        exit(0);
    }
    return ret;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        string curr = "";
        for (int j = 0; j < n; j++) curr += alph[i];
        cnt[i] = query(curr);
    }
    string pre = "";
    auto gr = [&] (char a, char b) {
        string curr = pre + a;
        for (int j = 0; j < cnt[b - 'a']; j++) curr += b;
        int ret = query(curr);
        if (ret == sz(curr)) return true;
        return false;
    };
    vector<char> vals;
    for (int i = 0; i < m; i++) vals.pb(alph[i]);
    sort(all(vals), [&] (char a, char b) {
        return gr(a, b);
    });
    auto upd = [&] () {
        char best = *(vals.begin());
        vals.erase(vals.begin());
        pre += best;
        cnt[best - 'a']--;
        if (cnt[best - 'a'] == 0) return;
        int lo = 0, hi = sz(vals) - 1;
        int ans = sz(vals);
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            if (!gr(best, vals[mid])) {
                lo = mid + 1;
            } else {
                hi = mid - 1;
                ans = mid;
            }
        }
        vals.insert(vals.begin() + ans, best);
    };
    upd();
    for (int i = 1; i < n; i++) {
        upd(); 
    }
    query(pre);
}

