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

bool F(vector<int>& a, int s) {
    for (auto p : a) {
        if (s < p) {
            return false;
        }
        ++s;
    }
    return true;
}

int Find_l(vector<int> a) {
    int l = 0;
    int r = 1000000005;

    while (l + 1 != r) {
        int m = (l + r) / 2;

        if (F(a, m) == true) {
            r = m;
        }
        else {
            l = m;
        }
    }

    return r;
}

int Find_r(vector<int> a, int p) {
    int r = a[p - 1];

    for (int i = p; i < a.size(); i++) {
        r = min(r, a[i] - (i - p + 1));
    }

    return r;
}

void Solve() {
    int n, p; cin >> n >> p;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());

    int l = Find_l(a);
    int r = Find_r(a, p);

    if (r > l) {
        cout << r - l << '\n';
        for (int i = l; i < r; i++) {
            cout << i << ' ';
        }
    }
    else {
        cout << 0;
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
