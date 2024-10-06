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

int Go_0(int mask, vector<int>& a) {
    int ans = 0;
    int last = a.size() - 1;
    while (mask) {
        if (mask % 2 == 0) {
            ans += a[last];
        }
        else {
            // pass
        }
        mask /= 2;
        --last;
    }
    for (int i = 0; i <= last; i++) {
        ans += a[i];
    }
    return ans;
}

int Go_1(int mask, vector<int>& a) {
    int ans = 0;
    int last = a.size() - 1;
    while (mask) {
        if (mask % 2 == 1) {
            ans += a[last];
        }
        else {
            // pass
        }
        mask /= 2;
        --last;
    }
    return ans;
}

int Solve(int mask, vector<int>& a) {
    int Sum0 = Go_0(mask, a);
    int Sum1 = Go_1(mask, a);
    return max(Sum0, Sum1);
}

void Solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int mx = 1;
    for (int i = 1; i < n; i++) {
        mx = mx * 2;
    }
    int ans = 1e18;
    for (int mask = 0; mask < mx; mask++) {
        int new_ans = Solve(mask, a);
        ans = min(ans, new_ans);
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
