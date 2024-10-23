#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>
#include <deque>
#include <array>
#include <list>
#include <stack>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <string>
#include <cstring>
#include <random>
#include <bitset>
#include <functional>
#include <iomanip>

using namespace std;

#define int long long

long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }

    return a;
}

void Solve() {
    int n, m, x, y, a, b;
    cin >> n >> m >> x >> y >> a >> b;
    int d = gcd(a, b);
    a /= d;
    b /= d;
    int t = min(n / a, m / b);
    a *= t;
    b *= t;
    int x1 = x - (a + 1) / 2;
    int y1 = y - (b + 1) / 2;
    int x2 = x - (a + 1) / 2 + a;
    int y2 = y - (b + 1) / 2 + b;
    if (x2 > n) {
        int r = x2 - n;
        x1 -= r;
        x2 -= r;
    }
    if (y2 > m) {
        int r = y2 - m;
        y1 -= r;
        y2 -= r;
    }
    if (x1 < 0) {
        int r = 0 - x1;
        x1 += r;
        x2 += r;
    }
    if (y1 < 0) {
        int r = 0 - y1;
        y1 += r;
        y2 += r;
    }
    cout << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int multitest = false;
    if (multitest == true) {
        int ctt; cin >> ctt;

        for (int i = 0; i < ctt; i++) {
            Solve();
        }
    }
    else {
        Solve();
    }

    return 0;
}
