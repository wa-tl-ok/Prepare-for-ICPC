//https://codeforces.com/contest/1722/problem/F

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

struct DSU {
    vector<int> head;
    vector<int> rang;
    vector<vector<int>> dist;

    DSU(int n, int nf, int mf) {
        head.resize(n);
        for (int i = 0; i < n; i++) {
            head[i] = i;
        }

        rang.resize(n);
        for (int i = 0; i < n; i++) {
            rang[i] = 1;
        }

        dist.resize(n);
        for (int i = 0; i < n; i++) {
            dist[i].push_back(i);
        }
    }

    int Find(int x) {
        if (head[x] == x) {
            return x;
        }
        return head[x] = Find(head[x]);
    }

    bool Union(int x, int y) {
        x = Find(x);
        y = Find(y);

        if (x == y) {
            return false;
        }

        if (rang[x] > rang[y]) {
            swap(x, y);
        }

        rang[y] += rang[x];
        for (auto p : dist[x]) {
            dist[y].push_back(p);
        }
        head[x] = y;

        return true;
    }
};

void Solve() {
    int n, m; cin >> n >> m;
    vector<vector<char>> M(n);
    for (int i = 0; i < n; i++) {
        M[i].resize(m);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> M[i][j];
            if (M[i][j] == '*') {
                M[i][j] = '#';
            }
        }
    }

    for (int i = 0; i < n - 2; i++) {
        for (int j = 0; j < m; j++) {
            if (M[i][j] == '#' && M[i + 1][j] == '#' && M[i + 2][j] == '#') {
                cout << "NO\n";
                return;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m - 2; j++) {
            if (M[i][j] == '#' && M[i][j + 1] == '#' && M[i][j + 2] == '#') {
                cout << "NO\n";
                return;
            }
        }
    }

    DSU dsu(n * m, n, m);

    auto F = [m](int i, int j) {
        return i * m + j; 
    };
    auto R = [m](int x) {
        return make_pair(x / m, x - (x / m) * m); 
    };
    auto D = [](pair<int, int> A, pair<int, int> B) {
        return abs(A.first - B.first) + abs(A.second - B.second); 
    };

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (M[i][j] == '#') {
                if (i - 1 >= 0 && j < m) {
                    int x = i - 1;
                    int y = j;

                    if (M[x][y] == '#') {
                        dsu.Union(F(i, j), F(x, y));
                    }
                }
                if (i < n && j - 1 >= 0) {
                    int x = i;
                    int y = j - 1;

                    if (M[x][y] == '#') {
                        dsu.Union(F(i, j), F(x, y));
                    }
                }
                if (i + 1 < n && j < m) {
                    int x = i + 1;
                    int y = j;

                    if (M[x][y] == '#') {
                        dsu.Union(F(i, j), F(x, y));
                    }
                }
                if (i < n && j + 1 < m) {
                    int x = i;
                    int y = j + 1;

                    if (M[x][y] == '#') {
                        dsu.Union(F(i, j), F(x, y));
                    }
                }
                if (i - 1 >= 0 && j - 1 >= 0) {
                    int x = i - 1;
                    int y = j - 1;

                    if (M[x][y] == '#') {
                        dsu.Union(F(i, j), F(x, y));
                    }
                }
                if (i + 1 < n && j - 1 >= 0) {
                    int x = i + 1;
                    int y = j - 1;

                    if (M[x][y] == '#') {
                        dsu.Union(F(i, j), F(x, y));
                    }
                }
                if (i - 1 >= 0 && j + 1 < m) {
                    int x = i - 1;
                    int y = j + 1;

                    if (M[x][y] == '#') {
                        dsu.Union(F(i, j), F(x, y));
                    }
                }
                if (i + 1 < n && j + 1 < m) {
                    int x = i + 1;
                    int y = j + 1;

                    if (M[x][y] == '#') {
                        dsu.Union(F(i, j), F(x, y));
                    }
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (M[i][j] == '#') {
                if (dsu.rang[dsu.Find(F(i, j))] != 3) {
                    cout << "NO\n";
                    return;
                }
                else {
                    vector<int> d = dsu.dist[dsu.Find(F(i, j))];
                    pair<int, int> A = R(d[0]);
                    pair<int, int> B = R(d[1]);
                    pair<int, int> C = R(d[2]);
                    if (max({ D(A, B) + D(B, C), D(B, C) + D(C, A), D(A, C) + D(C, B)}) > 3) {
                        cout << "NO\n";
                        return;
                    }
                }
            }
        }
    }

    cout << "YES\n";
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
