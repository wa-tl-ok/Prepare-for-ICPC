//https://codeforces.com/contest/2007/problem/D

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

int Play(string s, vector<int>& st, int h) {
    int ans = 0;
    for (int i = 1; i < s.size(); i++) {
        if (st[i] == 1) {
            if (s[i] != '?') {
                if (s[i] != s[0]) {
                    ans += 1;
                }
                else {
                    ans += 0;
                }
            }
            else {
                ans += h;
                h = (h + 1) % 2;
            }
        }
    }
    return ans;
}

vector<int> ANS;

void Solve() {
    int n; cin >> n;
    vector<int> st(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        st[u - 1] += 1; st[v - 1] += 1;
    }
    string s; cin >> s;

    if (s[0] != '?') {
        ANS.push_back(Play(s, st, 1));
    }
    else {
        int o = 0;
        int e = 0;
        for (int i = 1; i < n; i++) {
            if (st[i] == 1) {
                if (s[i] == '1') {
                    e += 1;
                }
                if (s[i] == '0') {
                    o += 1;
                }
            }
        }
        if (o > e) {
            s[0] = '1';
            ANS.push_back(Play(s, st, 0));
        }
        else if (o < e) {
            s[0] = '0';
            ANS.push_back(Play(s, st, 0));
        }
        else {
            int h = 0;
            for (int i = 1; i < n; i++) {
                if (st[i] == 1) {
                    // pass
                }
                else {
                    if (s[i] == '?') {
                        ++h;
                    }
                }
            }
            if (h % 2 == 0) {
                s[0] = '1';
                ANS.push_back(Play(s, st, 0));
            }
            else {
                s[0] = '0';
                ANS.push_back(Play(s, st, 1));
            }
        }
    }
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

        for (auto p : ANS) {
            cout << p << '\n';
        }
    }
    else {
        Solve();
    }

    return 0;
}
