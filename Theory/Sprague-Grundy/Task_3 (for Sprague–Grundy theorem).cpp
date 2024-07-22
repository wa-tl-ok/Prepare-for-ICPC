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

int dp[105];

int solve(int n) {
    if (dp[n] == -1) {
        set<int> s;

        if (n % 3 == 0) {
            s.insert(solve(n - 1));
            s.insert(solve(n - 2));
        }
        else if (n % 3 == 1) {
            s.insert(solve(n - 1));
            s.insert(solve(n - 3));
        }
        else {
            s.insert(solve(n - 1));
            s.insert(solve(n - 2));
            s.insert(solve(n - 3));
        }

        dp[n] = 0;
        while (s.find(dp[n]) != s.end()) {
            ++dp[n];
        }
    }

    return dp[n];
}

int main() {
    for (int i = 0; i < 105; i++) {
        dp[i] = -1;
    }

    dp[0] = 0;
    dp[1] = 1;
    dp[2] = 1;

    int n;
    cin >> n;

    if (solve(n)) {
        cout << 1;
    }
    else {
        cout << 2;
    }

    return 0;
}
