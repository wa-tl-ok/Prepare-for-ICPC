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

int Sum(int l, int r, vector<int>& pref) {
    if (l > r) {
        return 0;
    }
    ++l;
    ++r;
    return pref[r] - pref[l - 1];
}

void Solve() {
    int n; cin >> n;
    string s; cin >> s;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        if (s[i] == '0') {
            a[i] = 0;
        }
        else {
            a[i] = 1;
        }
    }

    vector<int> pref(n + 1);
    int pp = 0;
    for (int i = 0; i < n; i++) {
        pp += a[i];
        pref[i + 1] = pp;
    }

    int go = 0; double dist = 1e9;
    for (int i = 0; i <= n; i++) {
        int ALL_L = i;
        int ALL_R = n - i;

        int GOOD_L = i - Sum(0, i - 1, pref);
        int GOOD_R = Sum(i, n - 1, pref);

        if (GOOD_L * 2 >= ALL_L && GOOD_R * 2 >= ALL_R) {
            if (abs((double)n / 2 - i) < dist) {
                dist = abs((double)n / 2 - i);
                go = i;
            }
        }
    }

    cout << go;
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
