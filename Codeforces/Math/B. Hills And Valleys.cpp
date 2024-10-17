//https://codeforces.com/contest/1467/problem/B

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

void Solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<int> b(n);
    for (int i = 0; i < n; i++) {
        b[i] = a[i];
    }
    vector<int> p(n);
    for (int i = 1; i < n - 1; i++) {
        if (a[i] > a[i - 1] && a[i] > a[i + 1]) {
            p[i] = 1;
        }
        if (a[i] < a[i - 1] && a[i] < a[i + 1]) {
            p[i] = 1;
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans += p[i];
    }
    int mx = 0;
    for (int i = 1; i < n - 1; i++) {
        int f = 0;
        a[i] = b[i - 1];

        if (a[i] > a[i - 1] && a[i] > a[i + 1]) {
            ++f;
        }
        if (a[i] < a[i - 1] && a[i] < a[i + 1]) {
            ++f;
        }

        if (i - 1 >= 1) {
            if (a[i - 1] > a[i - 2] && a[i - 1] > a[i]) {
                ++f;
            }
            if (a[i - 1] < a[i - 2] && a[i - 1] < a[i]) {
                ++f;
            }
        }

        if (i + 1 <= n - 2) {
            if (a[i + 1] > a[i] && a[i + 1] > a[i + 2]) {
                ++f;
            }
            if (a[i + 1] < a[i] && a[i + 1] < a[i + 2]) {
                ++f;
            }
        }

        int s = 0;
        a[i] = b[i + 1];

        if (a[i] > a[i - 1] && a[i] > a[i + 1]) {
            ++s;
        }
        if (a[i] < a[i - 1] && a[i] < a[i + 1]) {
            ++s;
        }

        if (i - 1 >= 1) {
            if (a[i - 1] > a[i - 2] && a[i - 1] > a[i]) {
                ++s;
            }
            if (a[i - 1] < a[i - 2] && a[i - 1] < a[i]) {
                ++s;
            }
        }

        if (i + 1 <= n - 2) {
            if (a[i + 1] > a[i] && a[i + 1] > a[i + 2]) {
                ++s;
            }
            if (a[i + 1] < a[i] && a[i + 1] < a[i + 2]) {
                ++s;
            }
        }

        a[i] = b[i];

        mx = min(mx, min(f, s) - (p[i - 1] + p[i] + p[i + 1]));
    }

    cout << ans + mx << '\n';
}

int main() {
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
