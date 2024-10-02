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

int Pow(int a, int n) {
    int ans = 1;
    for (int i = 0; i < n; i++) {
        ans *= a;
    }
    return ans;
}

void Solve() {
    int n, l, r; cin >> n >> l >> r;

    int mi = 0;
    for (int i = 0; i < l; i++) {
        mi += Pow(2, i);
    }
    mi += (n - l);

    int ma = 0; int ost = n;
    for (int i = 0; i < min(n, r); i++) {
        ma += Pow(2, i);
        --ost;
    }
    ma += Pow(2, r - 1) * ost;

    cout << mi << ' ' << ma;
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
