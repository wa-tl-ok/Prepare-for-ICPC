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
    vector<pair<char, int>> stack;
    for (int i = 0; i < s.size(); i++) {
        if (stack.size() == 0) {
            stack.push_back({ s[i], i });
        }
        else {
            if (s[i] == '0') {
                if (stack[stack.size() - 1].first == '0') {
                    stack.push_back({ s[i], i });
                }
                else {
                    stack.pop_back();
                }
            }
            else {
                stack.push_back({ s[i], i });
            }
        }
    }
    string S = s;
    for (auto p : stack) {
        S[p.second] = '0';
    }
    cout << S;
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
