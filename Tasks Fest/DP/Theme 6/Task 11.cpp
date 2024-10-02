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

    int n; cin >> n;
    int m; cin >> m;

    vector<int> s(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
    }

    vector<vector<int>> DP(m + 1);
    for (int i = 0; i < m + 1; i++) {
        DP[i].resize(n + 1);
    }

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            DP[i][j] = 2e9;
        }
    }

    for (int i = 0; i <= n; i++) {
        DP[0][i] = 0;
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            DP[i][j] = DP[i][j - 1];

            if (i - s[j] >= 0) {
                DP[i][j] = min(DP[i][j], DP[i - s[j]][j - 1] + 1);
            }
        }
    }

    if (DP[m][n] == 2e9) {
        cout << 0;
    }
    else {
        cout << DP[m][n];
    }

    return 0;
}
