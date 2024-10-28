//https://codeforces.com/contest/1891/problem/C

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
    sort(a.begin(), a.end());
    int l = 0;
    int r = n - 1;
    int x = 0;
    int ans = 0;
    while (l < r) {
        if (x + a[l] >= a[r]) {
            a[l] -= (a[r] - x); ans += (a[r] - x);
            a[r] = 0; ++ans;
            x = 0;
        }
        else {
            x += a[l]; ans += a[l]; a[l] = 0;
        }
        if (a[l] == 0) {
            ++l;
        }
        if (a[r] == 0) {
            --r;
        }
    }
    int y = a[l];
    if (y > 0) {
        if (x >= y) {
            ++ans;
        }
        else {
            int ost = y - x;
            if (ost % 2 == 0) {
                ans += ost / 2 + 1;
            }
            else {
                if (a[l] == 1) {
                    ++ans;
                }
                else {
                    ++ost;
                    ans += ost / 2 + 1;
                }
            }
        }
    }
    cout << ans << '\n';
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
