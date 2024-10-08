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

#define int long long

void Solve() {
    int n, m; cin >> n >> m;

    vector<vector<int>> DP(n);
    for (int i = 0; i < n; i++) {
        DP[i].resize(m);
    }

    vector<vector<int>> A(n);
    for (int i = 0; i < n; i++) {
        A[i].resize(m);
    }

    vector<int> MIN(n);

    string s; cin >> s;
    MIN[0] = 1;
    for (int i = 0; i < m; i++) {
        if (s[i] == '0') {
            DP[0][i] = 1;
        }
        else {
            DP[0][i] = 0;
            MIN[0] = 0;
        }
        A[0][i] = s[i];
    }

    for (int i = 1; i < n; i++) {
        string s; cin >> s;
        int locmin = 1e18;
        for (int j = 0; j < m; j++) {
            if (s[j] == '1' && A[i - 1][j] == '1') {
                DP[i][j] = min(MIN[i - 1] + 1, DP[i - 1][j]);
            }
            else {
                DP[i][j] = MIN[i - 1] + 1;
            }
            locmin = min(locmin, DP[i][j]);
            A[i][j] = s[j];
        }
        MIN[i] = locmin;
    }

    int ans = 1e18;
    for (int i = 0; i < m; i++) {
        ans = min(ans, DP[n - 1][i]);
    }
    cout << ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int multitest = false;
    if (multitest == true) {
        int ctt; cin >> ctt;

        for (int i = 0; i < ctt; i++) {
            Solve();
        }
    }
    else {
        Solve();
    }

    return 0;
}
