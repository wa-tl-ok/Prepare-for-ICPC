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
#include <climits>

using namespace std;

void Solve() {
    int n; cin >> n;
    vector<string > v;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        v.push_back(s);
    }

    map<pair<int, int>, bool> cache;

    function<bool(int, int)> dfs = [&](int i, int mask) {
        auto key = make_pair(i, mask);
        if (cache[key]) {
            return cache[key];
        }
        bool ans = false;
        for (int j = 0; j < v.size(); j++) {
            if (mask & (1 << j)) {
                continue;
            }
            if (v[i][v[i].size() - 1] == v[j][0] && dfs(j, mask ^ (1 << j)) == false) {
                ans = true;
                break;
            }
        }
        cache[key] = ans;
        return ans;
    };

    for (int i = 0; i < n; i++) {
        if (dfs(i, 1 << i) == false) {
            cout << "First";
            return;
        }
    }
    cout << "Second";
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
