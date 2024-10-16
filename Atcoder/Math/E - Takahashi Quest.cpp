//https://atcoder.jp/contests/abc333/tasks/abc333_e

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
    int n; cin >> n;
    vector<pair<int, int>> e;
    for (int i = 0; i < n; i++) {
        int t; cin >> t;
        int x; cin >> x;
        e.push_back({ t, x });
    }
    reverse(e.begin(), e.end());
    multiset<int> need;
    vector<int> ans;
    for (int i = 0; i < n; i++) {
        int t = e[i].first;
        int x = e[i].second;
        if (t == 1) {
            if (need.find(x) != need.end()) {
                need.erase(need.find(x));
                ans.push_back(1);
            }
            else {
                ans.push_back(0);
            }
        }
        else {
            need.insert(x);
        }
    }
    if (need.size() > 0) {
        cout << -1;
        return;
    }
    else {
        reverse(ans.begin(), ans.end());
        reverse(e.begin(), e.end());
        int mx = 0; multiset<int> now; int k = 0;
        for (int i = 0; i < n; i++) {
            int t = e[i].first;
            int x = e[i].second;
            if (t == 1) {
                if (ans[k] == 1) {
                    now.insert(x);
                }
                ++k;
            }
            else {
                if (now.find(x) == now.end()) {
                    while (true) {

                    }
                }
                else {
                    now.erase(now.find(x));
                }
            }
            mx = max(mx, (int)now.size());
        }
        cout << mx << '\n';
        for (auto p : ans) {
            cout << p << ' ';
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
