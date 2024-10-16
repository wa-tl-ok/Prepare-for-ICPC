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

set<int> S;

bool c(int x) {
    if (S.find(x) != S.end()) {
        return true;
    }
    else {
        return false;
    }
}

void Solve() {
    int d; cin >> d;

    int p1 = -1;
    for (int i = d + 1; i < 100000; i++) {
        if (c(i) == true) {
            p1 = i;
            break;
        }
    }
    
    int p2 = -1;
    for (int i = p1 + d; i < 100000; i++) {
        if (c(i) == true) {
            p2 = i;
            break;
        }
    }

    cout << p1 * p2 << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    vector<bool> vis(100000, false);
    for (int i = 2; i < 100000; i++) {
        if (vis[i] == false) {
            S.insert(i);
            for (int j = i; j < 100000; j += i) {
                vis[j] = true;
            }
        }
    }

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
