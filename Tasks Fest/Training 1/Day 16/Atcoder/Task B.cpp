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

bool correct_h(char f, char s) {
    int d = (f - '0') * 10 + s - '0';
    return (d < 24);
}

bool correct_m(char f, char s) {
    int d = (f - '0') * 10 + s - '0';
    return (d < 60);
}

bool Good(int mv) {
    string h = to_string(mv / 60); if (h.size() == 1) h = "0" + h;
    string m = to_string(mv % 60); if (m.size() == 1) m = "0" + m;

    string s = "00:00";

    s[0] = h[0];
    s[1] = h[1];
    s[3] = m[0];
    s[4] = m[1];

    swap(s[1], s[3]);

    if (correct_h(s[0], s[1]) == true && correct_m(s[3], s[4]) == true) {
        return true;
    }
    else {
        return false;
    }
}

void Solve() {
    int h, m; cin >> h >> m;
    int cm = h * 60 + m;
    for (int i = 0; i <= 24 * 60; i++) {
        if (Good((cm + i) % (24 * 60)) == true) {
            cout << (cm + i) % (24 * 60) / 60 << ' ' << (cm + i) % (24 * 60) % 60;
            return;
        }
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
