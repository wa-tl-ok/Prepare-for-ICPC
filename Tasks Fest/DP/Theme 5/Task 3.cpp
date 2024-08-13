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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    string s1; cin >> s1;
    string s2; cin >> s2;

    int n = (int)s1.size();
    int m = (int)s2.size();

    vector<vector<int>> DP(n + 1);
    for (int i = 0; i <= n; i++) {
        DP[i].resize(m + 1);
    }

    DP[0][0] = 0;

    for (int i = 1; i <= n; i++) {
        DP[i][0] = i;
    }

    for (int j = 1; j <= m; j++) {
        DP[0][j] = j;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int ai = i - 1;
            int bj = j - 1;

            if (s1[ai] == s2[bj]) {
                DP[i][j] = DP[i - 1][j - 1];
            }
            else {
                DP[i][j] = min({ DP[i - 1][j], DP[i][j - 1], DP[i - 1][j - 1] }) + 1;
            }
        }
    }

    cout << DP[n][m];

    return 0;
}
