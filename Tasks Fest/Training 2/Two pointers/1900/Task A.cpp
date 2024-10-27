//https://codeforces.com/contest/1168/problem/B

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

bool good(string& s, int pos, int step) {
    if (pos + 2 * step >= s.size()) {
        return false;
    }
    else {
        if (s[pos] == s[pos + step] && s[pos + step] == s[pos + 2 * step]) {
            return true;
        }
        else {
            return false;
        }
    }
}

void Solve() {
    string s; cin >> s;
    int n = s.size();

    int L = 0;
    int R = n - 1;

    int ans = 0;

    while (true) {
        int ll = -1e18;
        int rr = 1e18;

        for (int l = L; l < min(n, L + 9); l++) {
            for (int step = 1; step <= 4; step++) {
                if (good(s, l, step)) {
                    if (l + 2 * step < rr) {
                        rr = l + 2 * step;
                        ll = l;
                    }
                }
            }
        }

        if (rr == 1e18) {
            break;
        }
        else {
            ans += (ll - L + 1) * (R - rr + 1);
            L = ll + 1;
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
