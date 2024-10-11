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

vector<int> ANS;

void Solve() {
    int n; cin >> n;
    string s; cin >> s;

    vector<int> c;

    int k = 0;
    for (int i = 0; i < n - 1; i++) {
        k += 1;
        if (s[i] != s[i + 1]) {
            c.push_back(k);
            k = 0;
        }
    }
    c.push_back(k + 1);

    for (int i = 0; i < c.size(); i++) {
        c[i] %= 2;
    }

    int ans = 0;

    while (c.size() > 1) {
        if (c[c.size() - 1] == 0) {
            c.pop_back();
        }
        else if (c[c.size() - 1] == 1 && c[c.size() - 2] == 1) {
            c.pop_back();
            c.pop_back();

            c.push_back(0);

            ++ans;
        }
        else {
            c.pop_back();
            c.pop_back();

            c.push_back(1);

            ++ans;
        }
    }

    ANS.push_back(ans);
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

        for (auto p : ANS) {
            cout << p << '\n';
        }
    }
    else {
        Solve();
    }

    return 0;
}
