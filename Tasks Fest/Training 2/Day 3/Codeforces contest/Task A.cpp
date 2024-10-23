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

void Solve() {
    int n, k; cin >> n >> k;
    if (n % 2 == 0) {
        cout << "YES\n";
    }
    else {
        if (n >= k) {
            if (k % 2 == 0) {
                if (n % 2 == 0) {
                    cout << "YES\n";
                }
                else {
                    cout << "NO\n";
                }
            }
            else {
                cout << "YES\n";
            }
        }
        else {
            cout << "NO\n";
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int multitest = true;
    if (multitest == true) {
        int ctt; cin >> ctt;
        for (; ctt-->0 ;) {
            Solve();
        }
    }
    else {
        Solve();
    }

    return 0;
}
