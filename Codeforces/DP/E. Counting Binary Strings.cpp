//https://codeforces.com/contest/1920/problem/E

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
    int n, m; 
    cin >> n >> m;

    vector<vector<int>> DP(n + 1);
    for (int i = 0; i <= n; i++) {
        DP[i].resize(m + 1);
    }

    for (int i = 1; i <= m; i++) {
        DP[0][i] = 1;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            for (int k = 1; k <= m; k++) {
                if (j * k > i) {
                    break;
                }

                if (j + k > m + 1) {
                    break;
                }

                DP[i][j] += DP[i - j * k][k];
                DP[i][j] %= 998244353;
            }
        }
    }

    int ans = 0;

    for (int i = 1; i <= m; i++) {
        ans += DP[n][i] % 998244353;
        ans %= 998244353;
    }

    cout << ans << endl;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int t; cin >> t;
    for (int i = 0; i < t; i++) {
        Solve();
    }

    return 0;
}
