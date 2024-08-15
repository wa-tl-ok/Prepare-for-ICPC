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
    int s; cin >> s;
    vector<int> dp(s + 1, 1e9);
    vector<int> pr(s + 1, 0);

    dp[0] = 0;
    for (int i = 1; i <= s; i++) {
        for (auto p : a) {
            if (i - p >= 0 && dp[i - p] != 1e9) {
                if (dp[i - p] < dp[i]) {
                    dp[i] = dp[i - p];
                    pr[i] = p;
                }
            }
        }
        if (dp[i] != 1e9) {
            ++dp[i];
        }
    }

    if (dp[s] == 1e9) {
        cout << "No solution";
        return 0;
    }

    vector<int> ans;
    while (s > 0) {
        ans.push_back(pr[s]);
        s -= pr[s];
    }
    reverse(ans.begin(), ans.end());

    for (int i = 0; i < (int)ans.size(); i++) {
        cout << ans[i] << ' ';
    }

    return 0;
}
