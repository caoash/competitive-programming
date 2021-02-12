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

const int MX = 10005;
const int MOD = (int) (1e9 + 7);
const ll INF = (ll) 1e18;

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

vi adj[MX];
int dp[MX];
int moves = 0;
int n;

void dfs(int v, int p, int len) {
    vi strands;
    for (int to : adj[v]) {
        if (to != p) {
            dfs(to, v, len);
            strands.pb(dp[to] + 1); 
            if (dp[to] == -1) dp[v] = -1;
        }
    }
    if (sz(strands) % 2 == 0 || v == 0) strands.pb(0);
    sort(all(strands));
    while (sz(strands) > 1) {
        int it = strands.back();
        strands.pop_back();
        if (it > len) {
            dp[v] = -1;
            break;
        } else {
            auto fir = upper_bound(all(strands), (len - it));
            if (fir == strands.begin()) {
                dp[v] = -1; 
                break;
            } else {
                --fir;
                strands.erase(fir);
                ++moves;
            }
        }
    }
    if (dp[v] != -1) {
        if (!strands.empty()) {
            dp[v] = *(strands.begin());
        }
    }
}

int main(){
    IO::init();
    IO::read_int(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v; 
        IO::read_int(u);
        IO::read_int(v);
        u--, v--;
        adj[u].pb(v), adj[v].pb(u);
    }
    int lo = 1, hi = n - 1;
    int ans = INT_MAX;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        memset(dp, 0, sizeof(dp));
        dfs(0, -1, mid);
        if (dp[0] == 0) {
            hi = mid - 1;
            ans = mid;
        } else {
            lo = mid + 1;
        }
    }
    moves = 0;
    memset(dp, 0, sizeof(dp));
    dfs(0, -1, ans);
    IO::write_int(moves, ' ');
    IO::write_int(ans);
}

