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
    int n; cin >> n;
    string s; cin >> s;

    int cnt = 0;
    for (int i = 0; i < n * 2; i++) {
        if (s[i] == '1') {
            ++cnt;
        }
    }

    if (cnt % 2 == 1) {
        cout << -1 << '\n';
        return;
    }

    vector<int> ans; bool was = 0;
    for (int i = 0; i < n; i++) {
        if (s[i * 2] != s[i * 2 + 1]) {
            if (was == 0) {
                if (s[i * 2] == '1') {
                    ans.push_back(i * 2 + 1);
                }
                else {
                    ans.push_back(i * 2 + 2);
                }
                was = 1;
            }
            else {
                if (s[i * 2] == '0') {
                    ans.push_back(i * 2 + 1);
                }
                else {
                    ans.push_back(i * 2 + 2);
                }
                was = 0;
            }
        }
    }

    cout << ans.size() << ' ';
    for (auto p : ans) {
        cout << p << ' ';
    }
    cout << '\n';

    for (int i = 1; i <= 2 * n; i += 2) {
        cout << i << ' ';
    }

    cout << '\n';
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
