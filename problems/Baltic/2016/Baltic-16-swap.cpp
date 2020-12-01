#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
 
#include <bits/stdc++.h> 
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
 
const int MX = 200005;

namespace IO {
    const int BUFFER_SIZE = 1 << 15;
 
    char input_buffer[BUFFER_SIZE];
    int input_pos = 0, input_len = 0;
 
    char output_buffer[BUFFER_SIZE];
    int output_pos = 0;
 
    char number_buffer[100];
    uint8_t lookup[100];
 
    void _update_input_buffer() {
        input_len = fread(input_buffer, sizeof(char), BUFFER_SIZE, stdin);
        input_pos = 0;
 
        if (input_len == 0)
            input_buffer[0] = EOF;
    }
 
    inline char next_char(bool advance = true) {
        if (input_pos >= input_len)
            _update_input_buffer();
 
        return input_buffer[advance ? input_pos++ : input_pos];
    }
 
    template<typename T>
    inline void read_int(T &number) {
        bool negative = false;
        number = 0;
 
        while (!isdigit(next_char(false)))
            if (next_char() == '-')
                negative = true;
 
        do {
            number = 10 * number + (next_char() - '0');
        } while (isdigit(next_char(false)));
 
        if (negative)
            number = -number;
    }
 
    template<typename T, typename... Args>
    inline void read_int(T &number, Args &... args) {
        read_int(number);
        read_int(args...);
    }
 
    void _flush_output() {
        fwrite(output_buffer, sizeof(char), output_pos, stdout);
        output_pos = 0;
    }
 
    inline void write_char(char c) {
        if (output_pos == BUFFER_SIZE)
            _flush_output();
 
        output_buffer[output_pos++] = c;
    }
 
    template<typename T>
    inline void write_int(T number, char after = '\0') {
        if (number < 0) {
            write_char('-');
            number = -number;
        }
 
        int length = 0;
 
        while (number >= 10) {
            uint8_t lookup_value = lookup[number % 100];
            number /= 100;
            number_buffer[length++] = (lookup_value & 15) + '0';
            number_buffer[length++] = (lookup_value >> 4) + '0';
        }
 
        if (number != 0 || length == 0)
            write_char(number + '0');
 
        for (int i = length - 1; i >= 0; i--)
            write_char(number_buffer[i]);
 
        if (after)
            write_char(after);
    }
 
    void init() {
        // Make sure _flush_output() is called at the end of the program.
        bool exit_success = atexit(_flush_output) == 0;
        assert(exit_success);
 
        for (int i = 0; i < 100; i++)
            lookup[i] = (i / 10 << 4) + i % 10;
    }
}
 
struct hash_pair { 
    template <class T1, class T2> 
    size_t operator()(const pair<T1, T2>& p) const
    { 
        auto hash1 = hash<T1>{}(p.first); 
        auto hash2 = hash<T2>{}(p.second); 
        return hash1 ^ hash2; 
    } 
}; 
 
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
 
int n; int num[MX]; gp_hash_table<pi, vi, hash_pair> dp; 
 
void merge(vi &best, vi a, int x, vi b) {
    vi ret;
    ret.pb(x);
    int p1 = 0, p2 = 0;
    for (int i = 0; i < 36; i++) {
        if (p1 < sz(a)) {
            for (int j = 0; j < (1 << i); j++) {
                if (p1 < sz(a)) {
                    ret.pb(a[p1++]);
                }
                else {
                    break;
                }
            } 
        }
        if (p2 < sz(b)) {
            for (int j = 0; j < (1 << i); j++) {
                if (p2 < sz(b)) {
                    ret.pb(b[p2++]);
                } 
                else {
                    break;
                }
            }
        }
    }
    if (best.empty()) best = ret;
    else best = min(best, ret);
}
 
vi solve(int v, int c) {
    if (!dp[mp(v, c)].empty()) {
        return dp[mp(v, c)];
    }
    int l = 2 * v + 1, r = 2 * v + 2;
    if (l >= n) {
        return dp[mp(v, c)] = {c};
    }
    if (r >= n) {
        vi best; 
        vi fst = solve(l, num[l]);
        best.pb(c);
        for (int x : fst) best.pb(x);
        vi sec = solve(l, c);
        vi sbest;
        sbest.pb(num[l]);
        for (int x : sec) sbest.pb(x);
        return dp[mp(v, c)] = min(best, sbest);
    }
    vi best;
    // no swaps
    merge(best, solve(l, num[l]), c, solve(r, num[r]));
 
    // swap left
    if (l < n) {
        merge(best, solve(l, c), num[l], solve(r, num[r]));
    }
 
    // swap right
    if (r < n) {
        merge(best, solve(l, num[l]), num[r], solve(r, c));
    }
 
    // swap left, then right
    if (r < n) {
        merge(best, solve(l, c), num[r], solve(r, num[l]));
    }
    return dp[mp(v, c)] = best;
}
 
int main(){
    IO::init();
    IO::read_int(n);
    for (int i = 0; i < n; i++) {
        IO::read_int(num[i]);
    }
    solve(0, num[0]); 
    vi ans = dp[mp(0, num[0])];
    for (int i = 0; i < n; i++) {
        IO::write_int((int) ans[i], ' ');
    }
}
