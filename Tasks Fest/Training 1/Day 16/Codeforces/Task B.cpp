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
    int n, k, g; 
    cin >> n >> k >> g;

    int s = k * g;

    int mx;
    if (g % 2 == 0) {
        mx = g / 2 - 1;
    }
    else {
        mx = g / 2;
    }

    int ans = n;
    int ss = n * mx;

    if (ss >= s) {
        cout << k * g << '\n';
    }
    else {
        int need = s - ss;

        int new_mx;
        if ((need + mx) % g <= mx) {
            new_mx = (need + mx) % g;
        }
        else {
            new_mx = -(g - (need + mx) % g);
        }

        cout << max(0LL, ss - mx + new_mx) << '\n';
    }
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
