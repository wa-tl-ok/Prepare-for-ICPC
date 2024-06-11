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
    int pers_mx;
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
        pers_mx = 1;
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
        pers_mx = mx;
 
        return true;
    }
 
    bool Persistent_Union(int x, int y) {
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
 
        pers_mx = max(pers_mx, rang[y]);
        condition.push_back({x, y, rang[x]});
 
        return true;
    }
 
    void Back() {
        mx = pers_mx;
 
        for (int i = (int)condition.size() - 1; i >= 0; i--) {
            auto T = condition[i];
 
            int x = T.x;
            int y = T.y;
            int sz = T.sz;
 
            head[x] = x;
            rang[y] -= sz;
        }
 
        condition.clear();
    }
};
 
void Solve() {
    int n, m; cin >> n >> m;
 
    vector<vector<char>> M(n);
    for (int i = 0; i < n; i++) {
        M[i].resize(m);
    }
 
    Persistent_DSU dsu(n * m);
 
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
 
    function<int(int, int)> num = [&](int x, int y) {
        return x * m + y;
    };
 
    function<void(int, int)> Merge = [&](int x, int y) {
        if (x == 0) {
            if (M[x][y] == '#' && M[x + 1][y] == '#') {
                dsu.Union(num(x, y), num(x + 1, y));
            }
        }
        else if (x == n - 1) {
            if (M[x][y] == '#' && M[x - 1][y] == '#') {
                dsu.Union(num(x, y), num(x - 1, y));
            }
        }
        else {
            if (M[x][y] == '#' && M[x + 1][y] == '#') {
                dsu.Union(num(x, y), num(x + 1, y));
            }
            if (M[x][y] == '#' && M[x - 1][y] == '#') {
                dsu.Union(num(x, y), num(x - 1, y));
            }
        }
        if (y == 0) {
            if (M[x][y] == '#' && M[x][y + 1] == '#') {
                dsu.Union(num(x, y), num(x, y + 1));
            }
        }
        else if (y == m - 1) {
            if (M[x][y] == '#' && M[x][y - 1] == '#') {
                dsu.Union(num(x, y), num(x, y - 1));
            }
        }
        else {
            if (M[x][y] == '#' && M[x][y + 1] == '#') {
                dsu.Union(num(x, y), num(x, y + 1));
            }
            if (M[x][y] == '#' && M[x][y - 1] == '#') {
                dsu.Union(num(x, y), num(x, y - 1));
            }
        }
    };
 
    function<void(int, int)> Merge_ = [&](int x, int y) {
        if (x == 0) {
            if (M[x][y] == '#' && M[x + 1][y] == '#') {
                dsu.Persistent_Union(num(x, y), num(x + 1, y));
            }
        }
        else if (x == n - 1) {
            if (M[x][y] == '#' && M[x - 1][y] == '#') {
                dsu.Persistent_Union(num(x, y), num(x - 1, y));
            }
        }
        else {
            if (M[x][y] == '#' && M[x + 1][y] == '#') {
                dsu.Persistent_Union(num(x, y), num(x + 1, y));
            }
            if (M[x][y] == '#' && M[x - 1][y] == '#') {
                dsu.Persistent_Union(num(x, y), num(x - 1, y));
            }
        }
        if (y == 0) {
            if (M[x][y] == '#' && M[x][y + 1] == '#') {
                dsu.Persistent_Union(num(x, y), num(x, y + 1));
            }
        }
        else if (y == m - 1) {
            if (M[x][y] == '#' && M[x][y - 1] == '#') {
                dsu.Persistent_Union(num(x, y), num(x, y - 1));
            }
        }
        else {
            if (M[x][y] == '#' && M[x][y + 1] == '#') {
                dsu.Persistent_Union(num(x, y), num(x, y + 1));
            }
            if (M[x][y] == '#' && M[x][y - 1] == '#') {
                dsu.Persistent_Union(num(x, y), num(x, y - 1));
            }
        }
    };
 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            Merge(i, j);
        }
    }
 
    function<int(int)> F_1 = [&](int x) {
        vector<char> was;
        for (int i = 0; i < m; i++) {
            was.push_back(M[x][i]);
            M[x][i] = '#';
        }
 
        for (int i = 0; i < m; i++) {
            Merge_(x, i);
        }
 
        int ans = dsu.pers_mx;
        dsu.Back();
 
        for (int i = 0; i < m; i++) {
            M[x][i] = was[i];
        }
 
        return ans;
    };
 
    function<int(int)> F_2 = [&](int y) {
        vector<char> was;
        for (int i = 0; i < n; i++) {
            was.push_back(M[i][y]);
            M[i][y] = '#';
        }
 
        for (int i = 0; i < n; i++) {
            Merge_(i, y);
        }
 
        int ans = dsu.pers_mx;
        dsu.Back();
 
        for (int i = 0; i < n; i++) {
            M[i][y] = was[i];
        }
 
        return ans;
    };
 
    int ans = 0;
 
    for (int i = 0; i < n; i++) {
        ans = max(ans, F_1(i));
    }
 
    for (int i = 0; i < m; i++) {
        ans = max(ans, F_2(i));
    }
 
    ANS.push_back(ans);
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
