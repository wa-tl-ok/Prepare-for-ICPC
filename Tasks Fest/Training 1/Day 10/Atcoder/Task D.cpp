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

set<int> P;

void Solve() {
    int n; cin >> n;
    for (auto e : P) {
        if (n % e == 0) {
            if ((n / e) % e == 0) {
                cout << e << ' ' << (n / e) / e << '\n'; return;
            }
            int p = sqrt(n / e);
            cout << p << ' ' << e << '\n'; return;
        }
    }
}

signed main() {
    vector<bool> v(3000000, true);
    for (int i = 2; i < v.size(); i++) {
        if (v[i] == true) {
            P.insert(i);
        }
        int j = i;
        while (j < v.size()) {
            v[j] = false;
            j += i;
        }
    }

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
