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
#include <iomanip>

using namespace std;

bool Pal(string s) {
    int i = 0;
    while (i < s.size() / 2) {
        int j = s.size() - 1 - i;
        if (s[i] != s[j]) {
            return false;
        }
        i++;
    }
    return true;
}

void Solve() {
    string s; cin >> s;

    string s1 = s + "a";

    if (!Pal(s1)) {
        cout << "YES" << '\n';
        cout << s1 << '\n';
        return;
    }

    string s2 = "a" + s;

    if (!Pal(s2)) {
        cout << "YES" << '\n';
        cout << s2 << '\n';
        return;
    }

    cout << "NO" << '\n';
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
