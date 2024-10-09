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

int go(int n) {
    return n * (n + 1) / 2;
}

void Solve() {
    int n; cin >> n;

    map<int, int> id1;
    for (int i = 1; i <= n; i++) {
        int t; cin >> t;
        id1[t] = i;
    }

    map<int, int> id2;
    for (int i = 1; i <= n; i++) {
        int t; cin >> t;
        id2[t] = i;
    }

    int ans = 0;

    int l = n;
    int r = 1;

    for (int x = 1; x <= n; x++) {
        int f = id1[x];
        int s = id2[x];

        if (f > s) {
            swap(f, s);
        }

        if (x == 1) {
            ans += go(f - 1);
            ans += go(n - s);
            if (f != s) {
                ans += go(s - f - 1);
            }
        }
        else {
            if (s < l) {
                ans += (l - s) * (n - r + 1);
            }
            else if (f > r) {
                ans += (f - r) * l;
            }
            if (f < l && s > r) {
                ans += (s - r) * (l - f);
            }
        }

        l = min(l, f);
        r = max(r, s);
    }

    cout << ans + 1 ;
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
