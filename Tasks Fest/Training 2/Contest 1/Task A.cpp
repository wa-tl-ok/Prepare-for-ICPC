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

bool good(int x) {
    if (x == 1) {
        return false;
    }
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) {
            return false;
        }
    }
    return true;
}

void Solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (auto x : a) {
        int sq;
        
        sq = sqrt(x) - 1;
        if (sq * sq == x) {
            if (good(sq) == true) {
                cout << "YES\n";
            }
            else {
                cout << "NO\n";
            }
            continue;
        }

        sq = sqrt(x);
        if (sq * sq == x) {
            if (good(sq) == true) {
                cout << "YES\n";
            }
            else {
                cout << "NO\n";
            }
            continue;
        }

        sq = sqrt(x) + 1;
        if (sq * sq == x) {
            if (good(sq) == true) {
                cout << "YES\n";
            }
            else {
                cout << "NO\n";
            }
            continue;
        }

        cout << "NO\n";
    }
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
