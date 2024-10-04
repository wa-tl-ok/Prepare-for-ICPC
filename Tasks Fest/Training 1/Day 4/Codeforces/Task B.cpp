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

vector<int> dp;

void Solve() {
    int x; cin >> x;
    if (x > 1000000) {
        cout << "YES" << '\n';
    }
    else {
        if (dp[x] == true) {
            cout << "YES" << '\n';
        }
        else {
            cout << "NO" << '\n';
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    dp.resize(1000000);
    for (int i = 0; i < dp.size(); i++) {
        dp[i] = false;
    }

    dp[11] = true;
    dp[111] = true;
    dp[1111] = true;
    dp[11111] = true;
    dp[111111] = true;

    for (int i = 12; i < dp.size(); i++) {
        if (i - 11 >= 0) {
            dp[i] = dp[i] | dp[i - 11];
        }
        if (i - 111 >= 0) {
            dp[i] = dp[i] | dp[i - 111];
        }
        if (i - 1111 >= 0) {
            dp[i] = dp[i] | dp[i - 1111];
        }
    }

    int multitest = true;
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
