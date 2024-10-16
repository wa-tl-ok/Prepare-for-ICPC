//https://atcoder.jp/contests/abc276/tasks/abc276_e

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

#define int long long

struct DSU {
    vector<int> head;
    vector<int> rang;

    DSU(int n) {
        head.resize(n);
        for (int i = 0; i < n; i++) {
            head[i] = i;
        }

        rang.resize(n);
        for (int i = 0; i < n; i++) {
            rang[i] = 1;
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
        }
    }

    auto F = [m](int i, int j) { 
        return i * m + j; 
    };

    vector<vector<int>> G(n * m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i - 1 >= 0) {
                if (M[i][j] != '#' && M[i - 1][j] != '#') {
                    G[F(i, j)].push_back(F(i - 1, j));
                    //cout << "Add: " << '[' << i << ", " << j << ']' << " and " << '[' << i - 1 << ", " << j << "]\n";
                }
            }
            if (i + 1 < n) {
                if (M[i][j] != '#' && M[i + 1][j] != '#') {
                    G[F(i, j)].push_back(F(i + 1, j));
                    //cout << "Add: " << '[' << i << ", " << j << ']' << " and " << '[' << i + 1 << ", " << j << "]\n";
                }
            }
            if (j - 1 >= 0) {
                if (M[i][j] != '#' && M[i][j - 1] != '#') {
                    G[F(i, j)].push_back(F(i, j - 1));
                    //cout << "Add: " << '[' << i << ", " << j << ']' << " and " << '[' << i << ", " << j - 1 << "]\n";
                }
            }
            if (j + 1 < m) {
                if (M[i][j] != '#' && M[i][j + 1] != '#') {
                    G[F(i, j)].push_back(F(i, j + 1));
                    //cout << "Add: " << '[' << i << ", " << j << ']' << " and " << '[' << i << ", " << j + 1 << "]\n";
                }
            }
        }
    }

    int x = -1;
    int y = -1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (M[i][j] == 'S') {
                x = i;
                y = j;
            }
        }
    }

    deque<int> now;
    vector<int> vis(n * m, -1);
    vis[F(x, y)] = 0; int k = 1;
    for (auto v : G[F(x, y)]) {
        vis[v] = ++k;
        now.push_back(v);
    }

    string ans = "No";
    DSU dsu(n * m);

    while (now.size() > 0) {
        int u = now[0];
        for (auto v : G[u]) {
            if (vis[v] == -1) {
                now.push_back(v);
                vis[v] = 1;
                dsu.Union(v, u);
                //cout << "New node : " << v << '\n';
            }
            else {
                if (v == F(x, y)) {
                    // pass
                }
                else {
                    if (dsu.Find(v) != dsu.Find(u)) {
                        //cout << "Get! ---> " << u << ' ' << v << '\n';
                        ans = "Yes";
                    }
                }
            }
        }
        now.pop_front();
    }
    cout << ans;
}

signed main() {
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
