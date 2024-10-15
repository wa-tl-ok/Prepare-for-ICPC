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
    int A, B, C, k;
    cin >> A >> B >> C >> k;

    for (int a = pow(10, A - 1); a < pow(10, A); a++) {
        int left = max(pow(10, C - 1) - a, pow(10, B - 1));
        int right = min(pow(10, C) - a, pow(10, B)) - 1;

        if (left > right) {
            continue;
        }

        int len = right - left + 1;
        if (k - len > 0) {
            k -= len;
        } 
        else {
            cout << a << " + " << left + k - 1 << " = " << a + left + k - 1 << '\n';
            return;
        }
    }

    cout << -1 << '\n';
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
