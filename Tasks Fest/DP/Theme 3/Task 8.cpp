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

int c[105][105];
int dp[105][105];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, m; cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> c[i][j];
        }
    }

    dp[1][1] = c[1][1];
    for (int i = 1; i <= n; i++) {
        dp[i][1] = dp[i - 1][1] + c[i][1];
    }
    for (int i = 1; i <= m; i++) {
        dp[1][i] = dp[1][i - 1] + c[1][i];
    }

    for (int i = 2; i <= n; i++) {
        for (int j = 2; j <= m; j++) {
            dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]) + c[i][j];
        }
    }

    cout << dp[n][m];

    return 0;
}
