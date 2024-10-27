//https://codeforces.com/contest/1610/problem/C

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

bool Check(vector<pair<int, int>>& v, int m) {
    int k = 0;
    int l = 0;
    int r = m;
    for (int i = 0; i < v.size(); i++) {
        if (v[i].first >= k && v[i].second >= m - k - 1) {
            ++k;
            ++l;
            ++r;
        }
        if (k == m) {
            return true;
        }
    }
    return false;
}

void Solve() {
    int n; cin >> n;
    vector<pair<int, int>> v;
    for (int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;
        v.push_back({ b, a });
    }
    int l = 0;
    int r = n + 1;
    while (l + 1 != r) {
        int m = (l + r) / 2;
        if (Check(v, m) == true) {
            l = m;
        }
        else {
            r = m;
        }
    }
    cout << l << '\n';
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
