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
    string s; cin >> s;
    string t; cin >> t;

    string p = "";
    for (int i = s.size() - t.size(); i < s.size(); i++) {
        p += s[i];
    }

    set<int> problem;
    for (int i = 0; i < t.size(); i++) {
        if (t[i] != p[i] && p[i] != '?' && t[i] != '?') {
            problem.insert(i);
        }
    }

    if (problem.size() == 0) {
        cout << "Yes\n";
    }
    else {
        cout << "No\n";
    }

    for (int i = 0; i < t.size(); i++) {
        p[i] = s[i];

        if (t[i] != p[i] && p[i] != '?' && t[i] != '?') {
            problem.insert(i);
        }
        else {
            problem.erase(i);
        }

        if (problem.size() == 0) {
            cout << "Yes\n";
        }
        else {
            cout << "No\n";
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
