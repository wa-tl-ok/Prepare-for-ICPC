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
    int n, m;
    cin >> n >> m;

    vector<int> M(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> M[i];
    }

    vector<int> C(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> C[i];
    }

    vector<vector<int>> DP(m + 1);
    for (int i = 0; i < m + 1; i++) {
        DP[i].resize(n + 1);
    }

    vector<vector<vector<int>>> ANS(m + 1);
    for (int i = 0; i < m + 1; i++) {
        ANS[i].resize(n + 1);
    }

    for (int i = 0; i < m + 1; i++) {
        DP[i][0] = 0;
    }

    for (int i = 0; i < n + 1; i++) {
        DP[0][i] = 0;
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            DP[i][j] = DP[i][j - 1];
            ANS[i][j] = ANS[i][j - 1];

            if (i - M[j] >= 0 && DP[i][j] < DP[i - M[j]][j - 1] + C[j]) {
                DP[i][j] = DP[i - M[j]][j - 1] + C[j];
                ANS[i][j] = ANS[i - M[j]][j - 1]; ANS[i][j].push_back(j);
            }
        }
    }

    vector<int> answer;
    int ans = 0;
    for (int i = 0; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (DP[i][j] > ans) {
                ans = DP[i][j];
                answer = ANS[i][j];
            }
        }
    }

    for (auto t : answer) {
        cout << t << '\n';
    }

    return 0;
}
