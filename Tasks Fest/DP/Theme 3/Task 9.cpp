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
char p[105][105];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, m; cin >> n >> m;
    vector<char> ans;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> c[i][j];
        }
    }

    dp[1][1] = c[1][1];
    p[1][1] = 'S';
    for (int i = 2; i <= n; i++) {
        dp[i][1] = dp[i - 1][1] + c[i][1];
        p[i][1] = 'D';
    }
    for (int i = 2; i <= m; i++) {
        dp[1][i] = dp[1][i - 1] + c[1][i];
        p[1][i] = 'R';
    }

    for (int i = 2; i <= n; i++) {
        for (int j = 2; j <= m; j++) {
            if (dp[i - 1][j] > dp[i][j - 1]) {
                dp[i][j] = dp[i - 1][j];
                p[i][j] = 'D';
            }
            else {
                dp[i][j] = dp[i][j - 1];
                p[i][j] = 'R';
            }
            dp[i][j] += c[i][j];
        }
    }

    cout << dp[n][m] << endl;

    while (n > 1 || m > 1) {
        ans.push_back(p[n][m]);

        if (p[n][m] == 'R') {
            m -= 1;
        }
        else {
            n -= 1;
        }
    }

    reverse(ans.begin(), ans.end());

    for (int i = 0; i < (int)ans.size(); i++) {
        cout << ans[i] << ' ';
    }

    return 0;
}
