//https://codeforces.com/contest/1985/problem/H1

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

vector<int> ANS;

struct Persistent_DSU {
    struct Trio {
        int x;
        int y;
        int sz;
    };

    int mx;
    vector<int> head;
    vector<int> rang;
    vector<Trio> condition;

    Persistent_DSU(int n) {
        head.resize(n);
        for (int i = 0; i < n; i++) {
            head[i] = i;
        }

        rang.resize(n);
        for (int i = 0; i < n; i++) {
            rang[i] = 1;
        }

        mx = 1;
    }

    int Find(int x) {
        if (head[x] == x) {
            return x;
        }
        return Find(head[x]);
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
        head[x] = y;

        mx = max(mx, rang[y]);
        condition.push_back({ x, y, rang[x] });

        return true;
    }

    void Back(int k) {
        for (int i = 0; i < k; i++) {
            auto T = condition[condition.size() - 1];

            int x = T.x;
            int y = T.y;
            int sz = T.sz;

            head[x] = x;
            rang[y] -= sz;

            condition.pop_back();
        }
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
        }
    }

    if (n == 1) {
        ANS.push_back(m);
        return;
    }

    if (m == 1) {
        ANS.push_back(n);
        return;
    }

    Persistent_DSU dsu(n * m);

    function<int(int, int)> num = [&](int x, int y) {
        return x * m + y;
    };

    function<int(int, int)> Merge = [&](int x, int y) {
        int Out = 0;
        if (x == 0) {
            if (M[x][y] == '#' && M[x + 1][y] == '#') {
                if (dsu.Union(num(x, y), num(x + 1, y))) {
                    ++Out;
                }
            }
        }
        else if (x == n - 1) {
            if (M[x][y] == '#' && M[x - 1][y] == '#') {
                if (dsu.Union(num(x, y), num(x - 1, y))) {
                    ++Out;
                }
            }
        }
        else {
            if (M[x][y] == '#' && M[x + 1][y] == '#') {
                if (dsu.Union(num(x, y), num(x + 1, y))) {
                    ++Out;
                }
            }
            if (M[x][y] == '#' && M[x - 1][y] == '#') {
                if (dsu.Union(num(x, y), num(x - 1, y))) {
                    ++Out;
                }
            }
        }
        if (y == 0) {
            if (M[x][y] == '#' && M[x][y + 1] == '#') {
                if (dsu.Union(num(x, y), num(x, y + 1))) {
                    ++Out;
                }
            }
        }
        else if (y == m - 1) {
            if (M[x][y] == '#' && M[x][y - 1] == '#') {
                if (dsu.Union(num(x, y), num(x, y - 1))) {
                    ++Out;
                }
            }
        }
        else {
            if (M[x][y] == '#' && M[x][y + 1] == '#') {
                if (dsu.Union(num(x, y), num(x, y + 1))) {
                    ++Out;
                }
            }
            if (M[x][y] == '#' && M[x][y - 1] == '#') {
                if (dsu.Union(num(x, y), num(x, y - 1))) {
                    ++Out;
                }
            }
        }
        return Out;
    };

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            Merge(i, j);
        }
    }

    vector<char> was;

    for (int x = 0; x < n; x++) {
        for (int i = 0; i < m; i++) {
            was.push_back(M[x][i]);
            M[x][i] = '#';
        }

        int B = 0;

        for (int i = 0; i < m; i++) {
            B += Merge(x, i);
        }

        dsu.Back(B);

        for (int i = 0; i < m; i++) {
            M[x][i] = was[i];
        }

        was.clear();
    }

    for (int y = 0; y < m; y++) {
        for (int i = 0; i < n; i++) {
            was.push_back(M[i][y]);
            M[i][y] = '#';
        }

        int B = 0;

        for (int i = 0; i < n; i++) {
            B += Merge(i, y);
        }

        dsu.Back(B);

        for (int i = 0; i < n; i++) {
            M[i][y] = was[i];
        }

        was.clear();
    }

    ANS.push_back(dsu.mx);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int test; cin >> test;

    for (int i = 0; i < test; i++) {
        Solve();
    }

    for (auto q : ANS) {
        cout << q << "\n";
    }

    return 0;
}
