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

int dp[10][10];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, m; cin >> n >> m;

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            dp[i][j] = 0;
        }
    }

    dp[1][1] = 1;
    dp[1][2] = 1;
    dp[1][3] = 1;
    dp[1][4] = 1;
    dp[1][5] = 1;
    dp[1][6] = 1;
    dp[1][7] = 1;
    dp[1][8] = 1;

    for (int i = 2; i <= 8; i++) {
        for (int j = 1; j <= 8; j++) {
            dp[i][j] = dp[i - 1][j + 1] + dp[i - 1][j - 1];
        }
    }

    cout << dp[8 - m + 1][n];

    return 0;
}
