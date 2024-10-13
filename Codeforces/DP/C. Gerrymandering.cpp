//https://codeforces.com/contest/2022/problem/C

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

map<pair<int, int>, int> DP;
int n; string s1, s2;

int countA(int x1, int y1, int x2, int y2, int x3, int y3) {
    y1--; y2--; y3--;
    int count = 0;
    if (x1 == 0 && s1[y1] == 'A') {
        count++;
    }
    else if (x1 == 1 && s2[y1] == 'A') {
        count++;
    }
    if (x2 == 0 && s1[y2] == 'A') {
        count++;
    }
    else if (x2 == 1 && s2[y2] == 'A') {
        count++;
    }
    if (x3 == 0 && s1[y3] == 'A') {
        count++;
    }
    else if (x3 == 1 && s2[y3] == 'A') {
        count++;
    }
    return count;
}

int F(int u, int d) {
    if (u == 0 && d == 0) {
        return 0;
    }
    if (DP.count({ u, d })) {
        return DP[{u, d}];
    }
    int MX = 0;
    if (u == d) {
        MX = max(MX, F(u - 1, d - 2) + (countA(0, u, 1, d, 1, d - 1) >= 2));
        MX = max(MX, F(u - 2, d - 1) + (countA(0, u, 1, d, 0, u - 1) >= 2));
        MX = max(MX, F(u - 3, d - 3) + (countA(0, u, 0, u - 1, 0, u - 2) >= 2) + (countA(1, d, 1, d - 1, 1, d - 2) >= 2));
    }
    if (u < d) {
        MX = max(MX, F(u - 1, d - 2) + (countA(0, u, 1, d, 1, d - 1) >= 2));
        if (u >= 3) {
            MX = max(MX, F(u - 3, d - 3) + (countA(0, u, 0, u - 1, 0, u - 2) >= 2) + (countA(1, d, 1, d - 1, 1, d - 2) >= 2));
        }
    }
    if (d < u) {
        MX = max(MX, F(u - 2, d - 1) + (countA(0, u, 1, d, 0, u - 1) >= 2));
        if (d >= 3) {
            MX = max(MX, F(u - 3, d - 3) + (countA(0, u, 0, u - 1, 0, u - 2) >= 2) + (countA(1, d, 1, d - 1, 1, d - 2) >= 2));
        }
    }
    DP[{u, d}] = MX;
    return MX;
}

void Solve() {
    cin >> n >> s1 >> s2; DP.clear();
    cout << F(n, n) << '\n';
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
