/*
 * R[X] where X > 2 can be represented as some combination of R[0], R[1], R[2] XOR together.
 * So, for some collision a ^ R[x] = b ^ R[y] for days x and y we can figure out a ^ b = R[x] ^ R[y].
 * Since a ^ b is constant, and R[x] ^ R[y] is some combination of R[0], R[1] and R[2] XOR together (some cancelling out), we can
 * figure out some R[z] using the collision by finding which R[z] has the same R[0], R[1], R[2] as R[x] ^ R[y] and set it to a ^ b.
 * Then, we can figure out R, and then figure out M easily. 
 *
 * To find queries, just randomly throw numbers till you hit them. It doesn't take that many queries.
 */

#include <bits/stdc++.h> 
#include "decrypt.h"
using namespace std;

using ll = long long;

using vi = vector<int>;
#define pb push_back
#define rsz resize
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using pi = pair<int,int>;
#define f first
#define s second
#define mp make_pair

mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());

const int MX = 256;

void decrypt(){
    int thonk[] = {4, 2, 1, 4 ^ 2, 2 ^ 1, 4 ^ 2 ^ 1, 4 ^ 1};
    vector<pair<int, pi>> qrys;
    vector<pi> done[256]; bool vis[256][8];
    int val[8], ret[256];
    int day = 0;
    memset(val, -1, sizeof(val));
    memset(ret, -1, sizeof(ret));
    for (int i = 0; i < 256; i++) done[i].clear();
    memset(vis, false, sizeof(vis));
    while(1) {
        int v = rnd() % MX;
        while(vis[v][day]) v = rnd() % MX;
        int r = query(v);
        for (pi x : done[r]) {
            if (x.s != day) {
                val[thonk[x.s] ^ thonk[day]] = x.f ^ v;
            }
        }
        bool fin = true;
        for (int i = 1; i <= 7; i++) {
            if (val[i] == -1) {
                fin = false;
            }
        }
        if (fin) {
            ++day;
            day %= 7;
            break;
        }
        done[r].pb(mp(v, day));
        qrys.pb(mp(v, mp(day, r)));
        vis[v][day] = true;
        ++day; 
        day %= 7;
    }
    for (auto x : qrys) {
        ret[val[thonk[x.s.f]] ^ x.f] = x.s.s;
    }
    for (int i = 0; i < MX; i++) {
        if (ret[i] == -1) {
            ret[i] = query(i ^ val[thonk[day]]);
            ++day;
            day %= 7;
        }
    }
    int temp[3];
    for (int i = 0; i < 3; i++) {
        temp[i] = val[thonk[i]];
    }
    solution(temp, ret);
    return;
}
