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

int Type(char c) {
    if (c != '?' && c != '*') {
        return 1;
    }
    else if (c == '?') {
        return 2;
    }
    else {
        return 3;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    string a; cin >> a;
    string b; cin >> b;

    int n = (int)a.size();
    int m = (int)b.size();

    vector<vector<string>> DP(n + 1);
    for (int i = 0; i <= n; i++) {
        DP[i].resize(m + 1);
    }

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            DP[i][j] = "No solution!";
        }
    }

    DP[0][0] = "";

    for (int i = 1; i <= n; i++) {
        int ai = i - 1;

        if (a[ai] == '*') {
            DP[i][0] = "";
        }

        else {
            break;
        }
    }

    for (int j = 1; j <= m; j++) {
        int bj = j - 1;

        if (b[bj] == '*') {
            DP[0][j] = "";
        }

        else {
            break;
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int ai = i - 1;
            int bj = j - 1;

            int at = Type(a[ai]);
            int bt = Type(b[bj]);

            if (at == 1 && bt == 1) { // letter && letter
                if (a[ai] == b[bj] && DP[i - 1][j - 1] != "No solution!") {
                    DP[i][j] = DP[i - 1][j - 1] + a[ai];
                }
            }
            else if (at == 1 && bt == 2) { // letter && ?
                if (DP[i - 1][j - 1] != "No solution!") {
                    DP[i][j] = DP[i - 1][j - 1] + a[ai];
                }
            }
            else if (at == 1 && bt == 3) { // letter && *
                if (DP[i - 1][j] == "No solution!" && DP[i][j - 1] == "No solution!") {
                    continue;
                }
                else {
                    if (DP[i - 1][j] == "No solution!") {
                        DP[i][j] = DP[i][j - 1];
                    }
                    else if (DP[i][j - 1] == "No solution!") {
                        DP[i][j] = DP[i - 1][j] + a[ai];
                    }
                    else {
                        if (DP[i - 1][j].size() + 1 < DP[i][j - 1].size()) {
                            DP[i][j] = DP[i - 1][j] + a[ai];
                        }
                        else {
                            DP[i][j] = DP[i][j - 1];
                        }
                    }
                }
            }
            else if (at == 2 && bt == 1) { // ? && letter
                if (DP[i - 1][j - 1] != "No solution!") {
                    DP[i][j] = DP[i - 1][j - 1] + b[bj];
                }
            }
            else if (at == 2 && bt == 2) { // ? && ?
                if (DP[i - 1][j - 1] != "No solution!") {
                    DP[i][j] = DP[i - 1][j - 1] + 'A';
                }
            }
            else if (at == 2 && bt == 3) { // ? && *
                if (DP[i - 1][j] == "No solution!" && DP[i][j - 1] == "No solution!") {
                    continue;
                }
                else {
                    if (DP[i - 1][j] == "No solution!") {
                        DP[i][j] = DP[i][j - 1];
                    }
                    else if (DP[i][j - 1] == "No solution!") {
                        DP[i][j] = DP[i - 1][j] + 'A';
                    }
                    else {
                        if (DP[i - 1][j].size() + 1 < DP[i][j - 1].size()) {
                            DP[i][j] = DP[i - 1][j] + 'A';
                        }
                        else {
                            DP[i][j] = DP[i][j - 1];
                        }
                    }
                }
            }
            else if (at == 3 && bt == 1) { // * && letter
                if (DP[i - 1][j] == "No solution!" && DP[i][j - 1] == "No solution!") {
                    continue;
                }
                else {
                    if (DP[i - 1][j] == "No solution!") {
                        DP[i][j] = DP[i][j - 1] + b[bj];
                    }
                    else if (DP[i][j - 1] == "No solution!") {
                        DP[i][j] = DP[i - 1][j];
                    }
                    else {
                        if (DP[i - 1][j].size() > DP[i][j - 1].size() + 1) {
                            DP[i][j] = DP[i][j - 1] + b[bj];
                        }
                        else {
                            DP[i][j] = DP[i - 1][j];
                        }
                    }
                }
            }
            else if (at == 3 && bt == 2) { // * && ?
                if (DP[i - 1][j] == "No solution!" && DP[i][j - 1] == "No solution!") {
                    continue;
                }
                else {
                    if (DP[i - 1][j] == "No solution!") {
                        DP[i][j] = DP[i][j - 1] + 'A';
                    }
                    else if (DP[i][j - 1] == "No solution!") {
                        DP[i][j] = DP[i - 1][j];
                    }
                    else {
                        if (DP[i - 1][j].size() > DP[i][j - 1].size() + 1) {
                            DP[i][j] = DP[i][j - 1] + 'A';
                        }
                        else {
                            DP[i][j] = DP[i - 1][j];
                        }
                    }
                }
            }
            else { // * && *
                if (DP[i - 1][j] == "No solution!" && DP[i][j - 1] == "No solution!") {
                    continue;
                }
                else {
                    if (DP[i - 1][j] == "No solution!") {
                        DP[i][j] = DP[i][j - 1];
                    }
                    else if (DP[i][j - 1] == "No solution!") {
                        DP[i][j] = DP[i - 1][j];
                    }
                    else {
                        if (DP[i - 1][j].size() > DP[i][j - 1].size()) {
                            DP[i][j] = DP[i][j - 1];
                        }
                        else {
                            DP[i][j] = DP[i - 1][j];
                        }
                    }
                }
            }
        }
    }

    cout << DP[n][m];

    return 0;
}
