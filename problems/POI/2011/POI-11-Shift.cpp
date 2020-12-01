#include <bits/stdc++.h> 
using namespace std;

using ll = long long;

using vi = vector<int>;
using vl = vector<ll>;
#define pb push_back
#define rsz resize
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using pi = pair<int,int>;
#define f first
#define s second
#define mp make_pair

const int MX = 200005;
const int MOD = (int) (1e9 + 7);
const ll INF = (ll) 1e18;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    vi a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[j] < a[i]) ++cnt;
        }
    }
    if (n % 2 == 1 && cnt % 2 == 1) {
        cout << "NIE DA SIE" << '\n';
        return 0;
    }
    int last = 2;
    vector<pair<char, int>> moves;
    auto dist = [&] (int i, int j) {
        if (i > j) {
            return i - j;
        }
        else {
            return (n - j) + i;
        }
    };
    auto swap3 = [&] (int i) {
        // dbg(i);
        if (last != i) {
            int req = dist(last, i);
            // dbg(last, i, req);
            moves.pb(mp('a', req));
            last = i;
        }
        moves.pb(mp('b', 1));
        int prev = (i - 1 < 0 ? n - 1 : i - 1);
        int two = (i - 2 < 0 ? n + i - 2 : i - 2);
        // dbg(i, prev, two);
        swap(a[i], a[two]);
        swap(a[i], a[prev]);
    };
    auto find = [&] (int v) {
        for (int j = 0; j < n; j++) {
            if (a[j] == v) {
                return j;
            }
        }
        return -1;
    };
    for (int i = 2; i <= n; i++) {
        int pos = find(i);
        if (a[(pos - 1 + n) % n] + 1 == i) {
            continue;
        }
        if (i <= n - 2) {
            int curr = pos;
            while (a[curr] != a[(curr - 1 + n) % n] + 1 && a[curr] != a[(curr - 2 + n) % n] + 1) {
                swap3(curr);
                curr = (curr - 2 + n) % n;
            }
            if (a[curr] == a[(curr - 2 + n) % n] + 1) {
                swap3((curr + 1) % n);
                swap3((curr + 1) % n);
            }
        }
        else {
            int curr = pos;
            while (a[curr] != a[(curr - 1 + n) % n] + 1) {
                swap3(curr);
                curr = (curr - 2 + n) % n;
            }
        }
        // dbg(a);
    }
    // dbg(a);
    // dbg(moves);
    // dbg(last);
    // dbg(a);
    int fst = find(1);
    if ((last - 2 + n) % n != fst) {
        moves.pb(mp('a', dist((last - 2 + n) % n, fst))); 
    }
    reverse(all(moves));
    vector<pair<char, int>> ret;
    while (!moves.empty()) {
        pair<char, int> fr = moves.back();
        if (ret.empty()) {
            ret.pb(fr);
        }
        else {
            if (fr.f == ret.back().f) {
                ret.back().s += fr.s;
            }
            else {
                ret.pb(fr);
            }
        }
        moves.pop_back();
    }
    cout << sz(ret) << '\n';
    for (auto x : ret) {
        cout << x.s << x.f << " ";
    }
}

