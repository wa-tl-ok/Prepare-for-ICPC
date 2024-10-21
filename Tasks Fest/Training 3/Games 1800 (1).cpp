//https://codeforces.com/contest/1190/problem/B

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

void f() {
    cout << "sjfnb";
}

void s() {
    cout << "cslnb";
}

void Play(vector<int>& a, int h) {
    vector<int> c;
    for (int i = 0; i < a.size(); i++) {
        c.push_back(i);
    }
    sort(a.begin(), a.end());
    int S = 0;
    for (int i = 0; i < a.size(); i++) {
        S += a[i] - c[i];
    }
    if (h == 0) {
        if (S % 2 == 0) {
            s();
        }
        else {
            f();
        }
    }
    else {
        if (S % 2 == 0) {
            f();
        }
        else {
            s();
        }
    }
}

void Solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int mx = 1;
    map<int, int> m;
    for (int i = 0; i < n; i++) {
        m[a[i]] += 1;
        mx = max(mx, m[a[i]]);
    }
    if (mx > 2) {
        s();
    }
    else if (mx == 2) {
        if (m[0] == 2) {
            s();
        }
        else {
            mx = 0;
            for (int i = 0; i < n; i++) {
                if (m[a[i]] == 2) {
                    a[i] -= 1;
                    break;
                }
            }
            m.clear();
            for (int i = 0; i < n; i++) {
                m[a[i]] += 1;
                mx = max(mx, m[a[i]]);
            }
            if (mx == 2) {
                s();
            }
            else {
                Play(a, 1);
            }
        }
    }
    else {
        Play(a, 0);
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
