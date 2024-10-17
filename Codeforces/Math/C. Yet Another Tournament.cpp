//https://codeforces.com/contest/1783/problem/C

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

int WIN_1(vector<int> a, int ind, int power) {
    int k = 0;
    vector<pair<int, int>> v;
    for (int i = 0; i < a.size(); i++) {
        v.push_back({ a[i], i });
    }
    sort(v.begin(), v.end());
    for (int i = 0; i < v.size(); i++) {
        if (v[i].second != ind) {
            if (v[i].first <= power) {
                power -= v[i].first;
                ++k;
            }
        }
    }
    return k;
}

int WIN_2(vector<int> a, int ind, int power) {
    int k = 0;
    vector<pair<int, int>> v;
    for (int i = 0; i < a.size(); i++) {
        if (i == ind) {
            if (power < a[ind]) {
                return -1;
            }
            else {
                power -= a[i];
                k += 1;
                a[i] = 1e18;
            }
        }
        v.push_back({ a[i], i });
    }
    sort(v.begin(), v.end());
    for (int i = 0; i < v.size(); i++) {
        if (v[i].second != ind) {
            if (v[i].first <= power) {
                power -= v[i].first;
                ++k;
            }
        }
    }
    return k;
}

void Solve() {
    int n; cin >> n;
    int power; cin >> power;

    vector<int> a(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int l = -1;
    int r = n;

    while (l + 1 != r) {
        int m = (l + r) / 2;

        if (WIN_1(a, m, power) >= m + 1 || WIN_2(a, m, power) >= m) {
            l = m;
        }
        else {
            r = m;
        }
    }

    cout << n - l << '\n';
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
