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
#include <iomanip>

using namespace std;

#define int long long

void Solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    if (n == 1) {
        cout << 0;
        return;
    }
    vector<int> dp(n);
    dp[0] = 1;
    for (int i = 1; i < n; i++) {
        if (dp[i - 1] > a[i]) {
            dp[i] = dp[i - 1];
        }
        else if (dp[i - 1] == a[i]) {
            dp[i] = dp[i - 1] + 1;
        }
        else {
            dp[i] = a[i] + 1;
        }
    }
    vector<int> h(n);
    h[n - 1] = dp[n - 1];
    for (int i = n - 2; i > 0; i--) {
        if (dp[i] == dp[i + 1] || dp[i] + 1 == dp[i + 1]) {
            h[i] = dp[i];
        }
        else {
            h[i] = dp[i + 1] - 1;
            dp[i] = dp[i + 1] - 1;
        }
    }
    h[0] = 1;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans += (h[i] - a[i] - 1);
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
