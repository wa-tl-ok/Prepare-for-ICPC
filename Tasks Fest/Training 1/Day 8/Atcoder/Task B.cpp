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

using namespace std;

#define int long long

void Solve() {
    int a, b, c, d, e, f; cin >> a >> b >> c >> d >> e >> f;
    a %= 998244353; b %= 998244353; c %= 998244353; d %= 998244353; e %= 998244353; f %= 998244353;
    cout << ((((a * b) % 998244353) * c) % 998244353 - (((d * e) % 998244353) * f) % 998244353 + 998244353) % 998244353;
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
