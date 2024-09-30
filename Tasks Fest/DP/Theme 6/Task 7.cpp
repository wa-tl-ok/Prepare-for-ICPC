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
    int n; cin >> n;
    vector<int> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }

    int S = 0;
    for (auto p : s) {
        S += p;
    }

    if (S % 2 == 1) {
        cout << "NO";
    }
    else {
        int m = S / 2;

        vector<vector<int>> DP(m + 1);
        for (int i = 0; i < m + 1; i++) {
            DP[i].resize(n + 1);
        }

        for (int i = 0; i < m + 1; i++) {
            DP[i][0] = false;
        }

        for (int i = 0; i < n + 1; i++) {
            DP[0][i] = true;
        }

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                DP[i][j] = false;

                if (DP[i][j - 1] == true) {
                    DP[i][j] = true;
                }

                if (i - s[j] >= 0 && DP[i - s[j]][j - 1] == true) {
                    DP[i][j] = true;
                }
            }
        }

        if (DP[m][n] == true) {
            cout << "YES";
        }
        else {
            cout << "NO";
        }
    }

    return 0;
}
