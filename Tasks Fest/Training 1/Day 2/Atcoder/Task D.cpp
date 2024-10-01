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
    string s; cin >> s;

    map<vector<int>, int> M;
    vector<int> a(10, 0);
    M[a] = 1;

    int ans = 0;

    for (int i = 0; i < s.size(); i++) {
        char c = s[i];

        int j = -1;
        if (c == '0') {
            j = 0;
        }
        if (c == '1') {
            j = 1;
        }
        if (c == '2') {
            j = 2;
        }
        if (c == '3') {
            j = 3;
        }
        if (c == '4') {
            j = 4;
        }
        if (c == '5') {
            j = 5;
        }
        if (c == '6') {
            j = 6;
        }
        if (c == '7') {
            j = 7;
        }
        if (c == '8') {
            j = 8;
        }
        if (c == '9') {
            j = 9;
        }

        a[j] = (a[j] + 1) % 2;
        ans += M[a];
        M[a] += 1;
    }

    cout << ans;
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
