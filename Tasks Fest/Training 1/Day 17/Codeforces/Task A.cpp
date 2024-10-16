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
    string s; cin >> s;

    vector<int> a;
    for (int i = 0; i < n; i++) {
        int p = s[i] - '0';
        a.push_back(p);
    }

    vector<int> b;
    for (int i = 0; i < n; i++) {
        b.push_back(1);
    }

    vector<int> c;
    for (int i = 0; i < n; i++) {
        c.push_back(a[i] + b[i]);
    }

    for (int i = 1; i < n; i++) {
        if (c[i] == c[i - 1]) {
            --c[i];
            --b[i];
            c[i] = max(c[i], 0);
            b[i] = max(b[i], 0);
        }
    }

    for (auto p : b) {
        cout << p;
    } cout << '\n';
}

int main() {
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
