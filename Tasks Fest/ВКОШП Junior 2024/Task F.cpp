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
    int m, n; cin >> n >> m;

    vector<int> a(n);
    vector<int> b(n);

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }

    int ans = 0;
    vector<int> ANS;

    for (int i = n - 1; i >= 0; i--) {
        if (a[i] <= b[i]) {
            ans += a[i];
        }
        else {
            ans += b[i];
        }

        if (i < m) {
            if (a[i] <= b[i]) {
                ANS.push_back(ans);
                break;
            }
            else {
                ANS.push_back(ans - b[i] + a[i]);
            }
        }
    }

    int mi = 1e18;
    for (auto p : ANS) {
        mi = min(mi, p);
    }

    cout << mi;
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
