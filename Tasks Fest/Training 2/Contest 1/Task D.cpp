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

#define int long long

bool is_num(char c) {
    set<char> C = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
    if (C.find(c) != C.end()) {
        return true;
    }
    return false;
}

bool is_let(char c) {
    set<char> C = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
    if (C.find(c) == C.end()) {
        return true;
    }
    return false;
}

void GO1(string& s) {
    vector<char> ff;
    vector<char> ss;
    for (int i = 0; i < s.size(); i++) {
        char l = s[i];
        char r = s[i + 1];
        ff.push_back(l);
        if (is_let(l) == 1 && is_num(r) == 1) {
            for (int j = i + 1; j < s.size(); j++) {
                ss.push_back(s[j]);
            }
            break;
        }
    }
    int x = 0;
    int st = 0;
    for (int i = ff.size() - 1; i >= 0; i--) {
        char c = ff[i];
        x += (int)(c - 'A' + 1) * pow(26, st);
        ++st;
    }
    cout << 'R';
    for (auto p : ss) {
        cout << p;
    }
    cout << 'C';
    cout << x;
    cout << '\n';
}

void FF(int x) {
    string s = "";
    while (x > 0) {
        int ost = (x - 1) % 26;
        x -= ost;
        if (is_let((char)(ost + 'A'))) s += (char)(ost + 'A');
        x = x / 26;
    }
    reverse(s.begin(), s.end());
    cout << s;
}

void GO2(string& s) {
    int x = 0;
    int y = 0;
    for (int i = 1; i < s.size(); i++) {
        if (is_num(s[i])) {
            x = x * 10 + (s[i] - '0');
        }
        else {
            for (int j = i + 1; j < s.size(); j++) {
                y = y * 10 + (s[j] - '0');
            }
            break;
        }
    }
    FF(y);
    cout << x;
    cout << '\n';
}

int T(string& s) {
    set<char> c = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
    int k = 0;
    for (int i = 0; i < s.size() - 1; i++) {
        if (c.find(s[i]) == c.end()) {
            if (c.find(s[i + 1]) != c.end()) {
                ++k;
            }
        }
        if (c.find(s[i]) != c.end()) {
            if (c.find(s[i + 1]) == c.end()) {
                ++k;
            }
        }
    }
    if (k > 1) {
        return 2;
    }
    else {
        return 1;
    }
}

void Solve() {
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        int type = T(s);
        if (type == 1) {
            GO1(s);
        }
        else {
            GO2(s);
        }
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
