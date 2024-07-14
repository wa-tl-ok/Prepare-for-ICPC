//https://atcoder.jp/contests/abc362/tasks/abc362_e

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
#include <random>

using namespace std;

const int mod = 998244353;
long long DP[81][81][81];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n; cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<int> ans(n + 1);
    ans[0] = -1;
    ans[1] = n;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            DP[2][i][j] = 1;
        }
    }

    for (int L = 3; L <= n; L++) {
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                for (int k = j + 1; k < n; k++) {
                    if (a[j] - a[i] == a[k] - a[j]) {
                        DP[L][j][k] += DP[L - 1][i][j];
                        DP[L][j][k] %= mod;
                    }
                }
            }
        }
    }

    for (int L = 2; L <= n; L++) {
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                ans[L] += DP[L][i][j];
                ans[L] %= mod;
            }
        }
    }

    for (auto p : ans) {
        if (p != -1) {
            cout << p << ' ';
        }
    }

    return 0;
}
