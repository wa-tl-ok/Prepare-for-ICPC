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

int go(int a, int b, int k) {
    if (k <= 0) {
        return 1e18;
    }
    else {
        return k - 1 + (a + k - 1) / k + (b + k - 1) / k;
    }
}

void Solve() {
    int a, b; cin >> a >> b;
    int ans = 1e18;
    for (int k = sqrt(max(a, b)) - 100000; k < sqrt(max(a, b)) + 100000; k++) {
        ans = min(ans, go(a, b, k));
    }
    cout << ans << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int multitest = true;
    if (multitest == true) {
        int ctt; cin >> ctt;
        for (; ctt-->0 ;) {
            Solve();
        }
    }
    else {
        Solve();
    }

    return 0;
}
