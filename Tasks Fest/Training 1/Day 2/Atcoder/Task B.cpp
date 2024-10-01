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
    int n, m; cin >> n >> m;
    vector<vector<char>> M(n);
    for (int i = 0; i < n; i++) {
        M[i].resize(m);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> M[i][j];
        }
    }

    set<pair<int, int>> C;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (M[i][j] == '1') {
                int D = 1;
                for (int i_ = 0; i_ < n; i_++) {
                    for (int j_ = 0; j_ < m; j_++) {
                        if (abs(i - i_) + abs(j - j_) <= D) {
                            C.insert(make_pair(i_, j_));
                        }
                    }
                }
            }
            if (M[i][j] == '2') {
                int D = 2;
                for (int i_ = 0; i_ < n; i_++) {
                    for (int j_ = 0; j_ < m; j_++) {
                        if (abs(i - i_) + abs(j - j_) <= D) {
                            C.insert(make_pair(i_, j_));
                        }
                    }
                }
            }
            if (M[i][j] == '3') {
                int D = 3;
                for (int i_ = 0; i_ < n; i_++) {
                    for (int j_ = 0; j_ < m; j_++) {
                        if (abs(i - i_) + abs(j - j_) <= D) {
                            C.insert(make_pair(i_, j_));
                        }
                    }
                }
            }
            if (M[i][j] == '4') {
                int D = 4;
                for (int i_ = 0; i_ < n; i_++) {
                    for (int j_ = 0; j_ < m; j_++) {
                        if (abs(i - i_) + abs(j - j_) <= D) {
                            C.insert(make_pair(i_, j_));
                        }
                    }
                }
            }
            if (M[i][j] == '5') {
                int D = 5;
                for (int i_ = 0; i_ < n; i_++) {
                    for (int j_ = 0; j_ < m; j_++) {
                        if (abs(i - i_) + abs(j - j_) <= D) {
                            C.insert(make_pair(i_, j_));
                        }
                    }
                }
            }
            if (M[i][j] == '6') {
                int D = 6;
                for (int i_ = 0; i_ < n; i_++) {
                    for (int j_ = 0; j_ < m; j_++) {
                        if (abs(i - i_) + abs(j - j_) <= D) {
                            C.insert(make_pair(i_, j_));
                        }
                    }
                }
            }
            if (M[i][j] == '7') {
                int D = 7;
                for (int i_ = 0; i_ < n; i_++) {
                    for (int j_ = 0; j_ < m; j_++) {
                        if (abs(i - i_) + abs(j - j_) <= D) {
                            C.insert(make_pair(i_, j_));
                        }
                    }
                }
            }
            if (M[i][j] == '8') {
                int D = 8;
                for (int i_ = 0; i_ < n; i_++) {
                    for (int j_ = 0; j_ < m; j_++) {
                        if (abs(i - i_) + abs(j - j_) <= D) {
                            C.insert(make_pair(i_, j_));
                        }
                    }
                }
            }
            if (M[i][j] == '9') {
                int D = 9;
                for (int i_ = 0; i_ < n; i_++) {
                    for (int j_ = 0; j_ < m; j_++) {
                        if (abs(i - i_) + abs(j - j_) <= D) {
                            C.insert(make_pair(i_, j_));
                        }
                    }
                }
            }
        }
    }

    for (auto P : C) {
        int x = P.first;
        int y = P.second;
        M[x][y] = '.';
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << M[i][j];
        } cout << '\n';
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
