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
    int n, x; cin >> n >> x;

    vector<bool> dp(x + 1, false);
    dp[0] = true;

    for (int z = 0; z < n; z++) {
        int a, b; cin >> a >> b;

        for (int i = dp.size() - 1; i >= 0; i--) {
            for (int j = 1; j <= b; j++) {
                if (i + j * a > x) {
                    break;
                }
                if (dp[i] == true) {
                    dp[i + j * a] = true;
                }
            }
        }
    }

    if (dp[x] == true) {
        cout << "Yes";
    }
    else {
        cout << "No";
    }
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
