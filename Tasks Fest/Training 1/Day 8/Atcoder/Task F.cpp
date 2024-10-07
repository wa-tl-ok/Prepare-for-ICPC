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

void Solve() {
    int n, m; cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<vector<int>> DP0(m + 1);
    vector<vector<int>> DP1(m + 1);

    for (int i = 0; i <= m; i++) {
        DP0[i].resize(n + 1);
        DP1[i].resize(n + 1);
    }

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            DP0[i][j] = 1e9;
            DP1[i][j] = 1e9;
        }
    }

    DP0[0][0] = 0;
    DP1[0][0] = 0;

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            DP0[i][j] = min(DP0[i][j - 1], DP1[i][j - 1] + 1);

            if (i > a[j - 1]) {
                DP1[i][j] = min(DP0[i - a[j - 1]][j - 1], DP1[i - a[j - 1]][j - 1]);
            }
            else if (i == a[j - 1]) {
                if (j != 1) {
                    DP1[i][j] = 1;
                }
                else {
                    DP1[i][j] = min(DP0[i - a[j - 1]][j - 1], DP1[i - a[j - 1]][j - 1]);
                }
            }
            else {
                // pass
            }
        }
    }

    vector<vector<int>> A(m + 1);
    for (int i = 0; i <= m; i++) {
        A[i].resize(n + 1);
    }

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            A[i][j] = min(DP0[i][j], DP1[i][j]);
        }
    }

    for (int i = 1; i <= m; i++) {
        if (A[i][n] == 1e9) {
            cout << -1 << '\n';
        }
        else {
            cout << A[i][n] << '\n';
        }
    }
}

int main() {
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
