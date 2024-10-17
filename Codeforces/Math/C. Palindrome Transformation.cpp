//https://codeforces.com/contest/486/problem/C

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

int DIST(char a, char b) {
    string alh = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz";

    int pos_a_1 = -1;
    int pos_a_2 = -1;
    int pos_b_1 = -1;
    int pos_b_2 = -1;

    for (int i = 0; i < alh.size(); i++) {
        if (alh[i] == a) {
            if (pos_a_1 == -1) {
                pos_a_1 = i;
            }
            else {
                pos_a_2 = i;
            }
        }
        if (alh[i] == b) {
            if (pos_b_1 == -1) {
                pos_b_1 = i;
            }
            else {
                pos_b_2 = i;
            }
        }
    }

    int d1 = abs(pos_a_1 - pos_b_1);
    int d2 = abs(pos_a_1 - pos_b_2);
    int d3 = abs(pos_a_2 - pos_b_1);
    int d4 = abs(pos_a_2 - pos_b_2);

    return min({ d1,d2,d3,d4 });
}

void Solve() {
    int n, p; cin >> n >> p;
    int ans = 0;

    if (p > (n + 1) / 2) {
        p = (n - p + 1);
    }

    string s; cin >> s; 

    int l = -1;
    for (int i = 1; i <= n / 2; i++) {
        if (DIST(s[i - 1], s[n - i]) != 0) {
            l = i;
            break;
        }
    }

    int r = -1;
    for (int i = 1; i <= n / 2; i++) {
        if (DIST(s[i - 1], s[n - i]) != 0) {
            r = i;
        }
    }
    
    if (l == -1 || r == -1) {
        cout << 0;
        return;
    }

    if (p < l) {
        ans = r - p;
    }
    else if (p > r) {
        ans = p - l;
    }
    else {
        ans = min(p - l, r - p) + (r - l);
    }

    for (int i = l; i <= r; i++) {
        ans += DIST(s[i - 1], s[n - i]);
    }

    cout << ans;
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
