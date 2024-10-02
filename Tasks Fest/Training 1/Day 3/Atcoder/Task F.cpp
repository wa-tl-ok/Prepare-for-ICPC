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
    int mod = 998244353;

    int N; cin >> N;

    string s; cin >> s; 
    s = "#" + s;

    int S = 0;

    vector<int> dp(N + 1);
    dp[0] = 1;
    dp[1] = s[1] - '0';

    S = dp[0] + dp[1];

    for (int i = 2; i <= N; i++) {
        int an = (int)(s[i] - '0');
        dp[i] = (dp[i - 1] * 10 % mod + an * S % mod) % mod;
        S = (S + dp[i]) % mod;
    }

    cout << dp[N];
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
