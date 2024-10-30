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

int MAX(vector<int> a) {
    int mx = 0;
    for (auto p : a) {
        mx = max(mx, p);
    }
    return mx;
}

void Solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int Flag = true;
    for (int i = 0; i < n - 1; i++) {
        if (a[i] != a[i + 1]) {
            Flag = false;
        }
    }
    if (Flag == true) {
        cout << 1 << '\n';
        for (int i = 0; i < n; i++) {
            cout << 1 << ' ';
        } 
        return;
    }
    vector<int> col(n);
    if (n % 2 == 0) {
        for (int i = 0; i < n; i++) {
            col[i] = i % 2 + 1;
        }
    }
    else {
        int id = -1;
        for (int i = 0; i < n - 1; i++) {
            if (a[i] == a[i + 1]) {
                id = i;
            }
        }
        if (id == -1) {
            if (a[0] == a[n - 1]) {
                for (int i = 0; i < n - 1; i++) {
                    col[i] = i % 2 + 1;
                }
                col[n - 1] = 1;
            }
            else {
                for (int i = 0; i < n - 1; i++) {
                    col[i] = i % 2 + 1;
                }
                col[n - 1] = 3;
            }
        }
        else {
            for (int i = 0; i <= id; i++) {
                col[i] = i % 2 + 1;
            }
            col[id + 1] = col[id];
            for (int i = id + 2; i < n; i++) {
                col[i] = (i + 1) % 2 + 1;
            }
        }
    }
    cout << MAX(col) << '\n';
    for (auto p : col) {
        cout << p << ' ';
    } cout << '\n';
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
