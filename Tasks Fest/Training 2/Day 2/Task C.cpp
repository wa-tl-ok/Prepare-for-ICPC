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
    if (n == 1 || n == 2) {
        cout << 1 << '\n';
        return;
    }
    vector<int> pos(n);
    for (int i = 0; i < n; i++) {
        pos[a[i]] = i;
    }
    vector<int> ans(n);
    ans[0] = 1;
    ans[1] = 1;
    int l = pos[0];
    int r = pos[1];
    if (l > r) {
        swap(l, r);
    }
    for (int i = 2; i < n; i++) {
        if (pos[i] > l && pos[i] < r) {
            ans[i] = r - l + 1 - i;
        }
        else {
            ans[i] = 1;
            if (pos[i] < l) {
                l = pos[i];
            }
            else {
                r = pos[i];
            }
        }
    }
    int go = 1;
    for (auto p : ans) {
        go *= p;
        go %= 1'000'000'007;
    }
    cout << go << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

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
