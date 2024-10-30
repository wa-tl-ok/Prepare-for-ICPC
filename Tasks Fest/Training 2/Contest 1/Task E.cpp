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

long double f(int hc, int h, int cc, int c) {
    return (long double)(hc * h + cc * c) / (long double)(hc + cc);
}

long double go(int h, int c, int a) {
    if (a < 0) return 1e18;
    else return (long double)((long double)h * (a / 2) + (long double)c * (a / 2) + (long double)((a % 2) * h)) / a;
}

void Solve() {
    int h, c, t; 
    cin >> h >> c >> t;

    int l = -1;
    int r = 1e6 + 5;
    while (l + 1 != r) {
        int m = (l + r) / 2;
        if (f(m + 1, h, m, c) > (long double)t) {
            l = m;
        }
        else {
            r = m;
        }
    }

    long double ans = 1e18;
    int best_x = -1;

    for (int i = -100; i <= 100; ++i) {
        int x = 2 * l + i;
        long double current_ans = abs(go(h, c, x) - t);

        if (current_ans < ans) {
            ans = current_ans;
            best_x = x;
        }
    }

    if (best_x % 2 == 0) {
        cout << 2 << '\n';
    }
    else {
        cout << best_x << '\n';
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int multitest = true;
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
