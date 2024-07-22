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

int dp[105][105];

int solve(int n, int m) {
    if (n > m) {
        swap(n, m);
    }
    if (dp[n][m] == -1) {
        set<int> s;

        for (int i = 1; i < m; i++) {
            s.insert(solve(n ,i) ^ solve(n, m - i));
        }

        for (int i = 1; i < n; i++) {
            s.insert(solve(i, m) ^ solve(n - i, m));
        }

        dp[n][m] = 0;
        while (s.find(dp[n][m]) != s.end()) {
            ++dp[n][m];
        }
    }

    return dp[n][m];
}

int main() {
    for (int i = 0; i < 105; i++) {
        for (int j = 0; j < 105; j++) {
            dp[i][j] = -1;
        }
    }

    int n, m, k;
    cin >> n >> m >> k;

    for (int i = 0; i <= k; i++) {
        dp[1][i] = 0;
    }

    if (solve(n, m)) {
        cout << 1;
    }
    else {
        cout << 2;
    }

    return 0;
}
