//https://codeforces.com/contest/1915/problem/E

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
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    set<int> s;
    int sum;

    s.clear();
    s.insert(0);
    sum = 0;
    for (int i = 0; i < n; i += 2) {
        int n1 = sum - a[i];
        if (s.find(n1) != s.end()) {
            cout << "YES\n";
            return;
        }
        if (i + 1 < n) {
            int r = a[i + 1] - a[i];
            sum += r;
            if (s.find(sum) != s.end()) {
                cout << "YES\n";
                return;
            }
            else {
                s.insert(sum);
            }
        }
    }

    s.clear();
    s.insert(0);
    sum = 0;
    for (int i = 1; i < n; i += 2) {
        int n1 = sum - a[i];
        if (s.find(n1) != s.end()) {
            cout << "YES\n";
            return;
        }
        if (i + 1 < n) {
            int r = a[i + 1] - a[i];
            sum += r;
            if (s.find(sum) != s.end()) {
                cout << "YES\n";
                return;
            }
            else {
                s.insert(sum);
            }
        }
    }

    cout << "NO\n";
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
