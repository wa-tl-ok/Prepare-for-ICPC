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

int dp[205];

int solve(int n) {
    if (dp[n] == -1) {
        set<int> s;

        for (int i = 1; i <= n; i++) {
            if (i == 1 || i == n) {
                s.insert(solve(n - 2) ^ 0);
            }
            else {
                int l = i - 2;
                int r = n - l - 3;

                s.insert(solve(l) ^ solve(r));
            }
        }

        dp[n] = 0;
        while (s.find(dp[n]) != s.end()) {
            ++dp[n];
        }
    }

    return dp[n];
}

int main() {
    for (int i = 0; i < 205; i++) {
        dp[i] = -1;
    }

    dp[0] = 0;
    dp[1] = 1;
    dp[2] = 1;

    int N;
    cin >> N;

    if (solve(N % 136)) {
        cout << "White";
    }
    else {
        cout << "Black";
    }

    return 0;
}
