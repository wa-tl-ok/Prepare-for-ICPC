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

bool g(int x, int y) {
    if (x < 0 || x >= 9) {
        return false;
    }
    if (y < 0 || y >= 9) {
        return false;
    }
    return true;
}

void Solve() {
    vector<vector<char>> A(9);
    for (int i = 0; i < 9; i++) {
        A[i].resize(9);
    }

    for (int i = 0; i < 9; i++) {
        string s; cin >> s;
        for (int j = 0; j < s.size(); j++) {
            A[i][j] = s[j];
        }
    }

    int ans = 0;

    for (int x1 = 0; x1 < 9; x1++) {
        for (int y1 = 0; y1 < 9; y1++) {
            if (A[x1][y1] == '#') {
                for (int i = 0; i < 10; i++) {
                    for (int j = 0; j < 10; j++) {
                        if (i + j == 0) {
                            continue;
                        }

                        int x2 = x1 + i;
                        int y2 = y1 + j;

                        int x3 = x2 + j;
                        int y3 = y2 - i;

                        int x4 = x3 - i;
                        int y4 = y3 - j;

                        if (g(x2, y2) && g(x3, y3) && g(x4, y4)) {
                            if (A[x2][y2] == '#') {
                                if (A[x3][y3] == '#') {
                                    if (A[x4][y4] == '#') {
                                        ++ans;
                                    }
                                }
                            }
                        }
                    }
                }

                A[x1][y1] = '.';
            }
        }
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
