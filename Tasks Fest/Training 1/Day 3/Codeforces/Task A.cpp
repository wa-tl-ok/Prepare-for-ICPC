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

int Count(string s, char c) {
    int k = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == c) {
            ++k;
        }
    }
    return k;
}

void Solve() {
    string s; cin >> s;
    if (Count(s, '0') == s.size()) {
        cout << 0 << '\n';
    }
    else if (Count(s, '1') == 1) {
        cout << s.size() / 2 << '\n';
    }
    else {
        cout << (s.size() + 1) / 2 << '\n';
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
