#include <bits/stdc++.h>

int main() {
    std::ios::sync_with_stdio(false);

    std::function<long long(long long, long long, long long&, long long&)> ext_gcd;
    ext_gcd = [&ext_gcd](long long a, long long b, long long& x, long long& y) -> long long {
        long long d = a;
        if(b != 0) {
            d = ext_gcd(b, a % b, y, x);
            y -= (a / b) * x;
        } else {
            x = 1;
            y = 0;
        }
        return d;
    };

    long long a, b, c;
    long long x1, x2;
    long long y1, y2;

    std::cin >> a >> b >> c;
    std::cin >> x1 >> x2;
    std::cin >> y1 >> y2;

    c = -c;
    if (c < 0) {
       c = -c;
       a = -a;
       b = -b;
    }
    if (a < 0) {
        a = -a;
        auto tmp = x1;
        x1 = -x2;
        x2 = -tmp;
    }
    if (b < 0) {
        b = -b;
        auto tmp = y1;
        y1 = -y2;
        y2 = -tmp;
    }

    long long res = 0;
    if (a == 0 && b == 0) {
        res = c == 0 ? (x2 - x1 + 1) * (y2 - y1 + 1) : 0;
    } else if (a == 0 && b != 0) {
        long long tmp_y = c / b;
        res = (c % b == 0 && tmp_y >= y1 && tmp_y <= y2) ? (x2 - x1 + 1) : 0;
    } else if (a != 0 && b == 0) {
        long long tmp_x = c / a;
        res = (c % a == 0 && tmp_x >= x1 && tmp_x <= x2) ? (y2 - y1 + 1) : 0;
    } else {
        long long x, y;
        long long gcd = ext_gcd(a, b, x, y);
        if(c % gcd != 0) {
            res = 0;
        } else {
            long long kx, ky;
            x *= c / gcd;
            y *= c / gcd;
            kx = b / gcd;
            ky = -a / gcd;
            long long left = std::max(std::ceil(1.0 * (x1 - x) / kx) , std::ceil(1.0 * (y2 - y) / ky));
            long long right = std::min(std::floor(1.0 * (x2 - x) / kx), std::floor(1.0 * (y1 - y) / ky));
            res = left > right ? 0 : std::max(0LL, right - left + 1);
        }
    }

    std::cout << res << std::endl;
    return 0;
}
