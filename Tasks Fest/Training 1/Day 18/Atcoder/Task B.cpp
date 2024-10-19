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

int Front(vector<int>& a, int now, int need) {
    int ans = 0;
    while (now != need) {
        ++ans;
        ++now;
        if (now == a.size()) {
            now = 0;
        }
        if (a[now] == 1) {
            return 1e18;
        }
    }
    return ans;
}

int Back(vector<int>& a, int now, int need) {
    int ans = 0;
    while (now != need) {
        ++ans;
        --now;
        if (now == -1) {
            now = a.size() - 1;
        }
        if (a[now] == 1) {
            return 1e18;
        }
    }
    return ans;
}

void Solve() {
    int n, q; cin >> n >> q;
    int L = 0; int R = 1;
    vector<int> a(n);
    a[L] = 1;
    a[R] = 1;
    int ans = 0;
    for (int i = 0; i < q; i++) {
        char c; int k; cin >> c >> k; --k;
        if (c == 'L') {
            ans += min(Front(a, L, k), Back(a, L, k));
            a[L] = 0;
            L = k;
            a[L] = 1;
        }
        else {
            ans += min(Front(a, R, k), Back(a, R, k));
            a[R] = 0;
            R = k;
            a[R] = 1;
        }
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
