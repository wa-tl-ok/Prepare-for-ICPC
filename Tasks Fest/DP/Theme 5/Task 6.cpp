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
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    set<int> as;
    for (int i = 0; i < n; i++) {
        as.insert(a[i]);
    }

    vector<int> b;
    for (auto p : as) {
        b.push_back(p);
    }
    int m = (int)b.size();

    vector<vector<int>> DP(n + 1);
    for (int i = 0; i <= n; i++) {
        DP[i].resize(m + 1);
    }

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            DP[i][j] = 0;
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int ai = i - 1;
            int bj = j - 1;

            if (a[ai] == b[bj]) {
                DP[i][j] = DP[i - 1][j - 1] + 1;
            }

            DP[i][j] = max(DP[i][j], DP[i][j - 1]);
            DP[i][j] = max(DP[i][j], DP[i - 1][j]);
        }
    }

    vector<int> ans;

    while (DP[n][m] > 0) {
        if (a[n - 1] == b[m - 1]) {
            ans.push_back(a[n - 1]);

            --n;
            --m;
        }
        else {
            if (DP[n - 1][m] == DP[n][m]) {
                --n;
            }
            else {
                --m;
            }
        }
    }

    reverse(ans.begin(), ans.end());

    for (int i = 0; i < (int)ans.size(); i++) {
        cout << ans[i] << ' ';
    }

    return 0;
}
