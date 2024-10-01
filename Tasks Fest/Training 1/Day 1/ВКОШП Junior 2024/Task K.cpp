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
    int n, m, p; cin >> n >> m >> p;
    vector<int> DP(n + 1);
    for (int i = n; i >= p; i--) {
        if (i * m > n) {
            DP[i] = true;
        }
        else {
            int f = false;

            for (int t = 2; t <= m; t++) {
                if (DP[t * i] == false) {
                    f = true;
                }
            }

            DP[i] = f;
        }

        if (i == p) {
            if (DP[i]) {
                cout << "first";
            }
            else {
                cout << "second";
            }
        }
    }
}

int main() {
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
