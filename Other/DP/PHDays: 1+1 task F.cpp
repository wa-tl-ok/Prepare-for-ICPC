https://contest.yandex.ru/contest/62775/problems/F/

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
#include <random>

using namespace std;

long long DP[205][105][105];
long long mod = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    string s; cin >> s;

    for (int i = 0; i < 205; i++) {
        for (int j = 0; j < 105; j++) {
            for (int k = 0; k < 105; k++) {
                DP[i][j][k] = 0;
            }
        }
    }

    if (s[0] == 'X' || s[0] == '*') {
        DP[0][1][0] = 1;
    }
    else if (s[0] == 'U' || s[0] == '#') {
        DP[0][0][1] = 1;
    }
    else if (s[0] == '?') {
        DP[0][1][0] = 1;
        DP[0][0][1] = 1;
    }

    for (int i = 1; i < (int)s.size(); i++) {
        if (s[i] == 'X') {
            for (int b1 = 1; b1 < 103; b1++) {
                for (int b2 = 0; b2 < 103; b2++) {
                    DP[i][b1][b2] += DP[i - 1][b1 - 1][b2];
                    DP[i][b1][b2] %= mod;
                }
            }
        }
        if (s[i] == 'Y') {
            for (int b1 = 0; b1 < 103; b1++) {
                for (int b2 = 0; b2 < 103; b2++) {
                    DP[i][b1][b2] += DP[i - 1][b1 + 1][b2];
                    DP[i][b1][b2] %= mod;
                }
            }
        }
        if (s[i] == 'U') {
            for (int b1 = 0; b1 < 103; b1++) {
                for (int b2 = 1; b2 < 103; b2++) {
                    DP[i][b1][b2] += DP[i - 1][b1][b2 - 1];
                    DP[i][b1][b2] %= mod;
                }
            }
        }
        if (s[i] == 'V') {
            for (int b1 = 0; b1 < 103; b1++) {
                for (int b2 = 0; b2 < 103; b2++) {
                    DP[i][b1][b2] += DP[i - 1][b1][b2 + 1];
                    DP[i][b1][b2] %= mod;
                }
            }
        }
        if (s[i] == '*') {
            for (int b1 = 0; b1 < 103; b1++) {
                for (int b2 = 0; b2 < 103; b2++) {
                    if (b1 == 0) {
                        DP[i][b1][b2] += DP[i - 1][b1 + 1][b2];
                        DP[i][b1][b2] %= mod;
                    }
                    else {
                        DP[i][b1][b2] += DP[i - 1][b1 + 1][b2] + DP[i - 1][b1 - 1][b2];
                        DP[i][b1][b2] %= mod;
                    }
                }
            }
        }
        if (s[i] == '#') {
            for (int b1 = 0; b1 < 103; b1++) {
                for (int b2 = 0; b2 < 103; b2++) {
                    if (b2 == 0) {
                        DP[i][b1][b2] += DP[i - 1][b1][b2 + 1];
                        DP[i][b1][b2] %= mod;
                    }
                    else {
                        DP[i][b1][b2] += DP[i - 1][b1][b2 + 1] + DP[i - 1][b1][b2 - 1];
                        DP[i][b1][b2] %= mod;
                    }
                }
            }
        }
        if (s[i] == '?') {
            for (int b1 = 0; b1 < 103; b1++) {
                for (int b2 = 0; b2 < 103; b2++) {
                    if (b1 == 0 && b2 == 0) {
                        DP[i][b1][b2] += DP[i - 1][b1][b2 + 1] + DP[i - 1][b1 + 1][b2];
                        DP[i][b1][b2] %= mod;
                    }
                    else if (b1 == 0) {
                        DP[i][b1][b2] +=
                            DP[i - 1][b1 + 1][b2] +
                            DP[i - 1][b1][b2 - 1] +
                            DP[i - 1][b1][b2 + 1];
                        DP[i][b1][b2] %= mod;
                    }
                    else if (b2 == 0) {
                        DP[i][b1][b2] +=
                            DP[i - 1][b1][b2 + 1] +
                            DP[i - 1][b1 - 1][b2] +
                            DP[i - 1][b1 + 1][b2];
                        DP[i][b1][b2] %= mod;
                    }
                    else {
                        DP[i][b1][b2] +=
                            DP[i - 1][b1][b2 + 1] +
                            DP[i - 1][b1][b2 - 1] +
                            DP[i - 1][b1 - 1][b2] +
                            DP[i - 1][b1 + 1][b2];
                        DP[i][b1][b2] %= mod;
                    }
                }
            }
        }
    }

    cout << DP[s.size() - 1][0][0];

    return 0;
}
