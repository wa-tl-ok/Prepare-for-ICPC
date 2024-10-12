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

void Solve() {
    int a, b; cin >> a >> b;

    int F = 0;
    if (b == 1) {
        ++F;
        b = 2;
    } int ans = 1e9;

    int ca = a;
    int cb = b;

    for (int p = 0; p <= 1000; p++) {
        ca = a;
        cb = b + p;

        int q = F + p;

        while (ca != 0) {
            ca /= cb;
            q++;
        }

        ans = min(ans, q);
    }

    cout << ans << '\n';
}

int main() {
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
