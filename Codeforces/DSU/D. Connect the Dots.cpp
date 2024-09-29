//https://codeforces.com/contest/2020/problem/D

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
    int size;

    DSU(int n) {
        head.resize(n);
        for (int i = 0; i < n; i++) {
            head[i] = i;
        }

        rang.resize(n);
        for (int i = 0; i < n; i++) {
            rang[i] = 1;
        }

        size = n;
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

        size--;

        return true;
    }

    void Merge(int l, int r, int d) {
        for (int i = l; i <= r - d; i += d) {
            Union(i, i + d);
        }
    }

    int Size() {
        return size;
    }
};

vector<int> ans;

void Solve() {
    int n, m; cin >> n >> m;
    DSU dsu(n + 1);

    map<int, vector<pair<int, int>>> D;
    for (int i = 0; i < m; i++) {
        int a, d, k; cin >> a >> d >> k;
        D[d].push_back({ a, k });
    }

    for (int d = 1; d <= 10; d++) {
        vector<pair<int, int>> seg = D[d];
        map<int, vector<pair<int, int>>> Time_line;

        for (auto P : seg) {
            int a = P.first;
            int k = P.second;

            int ost = a % d;

            Time_line[ost].push_back(make_pair(a, a + d * k));
        }

        for (int ost = 0; ost < d; ost++) {
            sort(Time_line[ost].begin(), Time_line[ost].end());
        }

        for (int ost = 0; ost < d; ost++) {
            if (Time_line[ost].size() > 0) {
                int last = Time_line[ost][0].first;

                for (int i = 0; i < Time_line[ost].size(); i++) {
                    if (Time_line[ost][i].first <= last) {
                        if (Time_line[ost][i].second > last) {
                            dsu.Merge(last, Time_line[ost][i].second, d);
                            last = Time_line[ost][i].second;
                        }
                    }
                    else {
                        dsu.Merge(Time_line[ost][i].first, Time_line[ost][i].second, d);
                        last = Time_line[ost][i].second;
                    }
                }
            }
        }
    }

    ans.push_back(dsu.Size() - 1);
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

        for (auto p : ans) {
            cout << p << '\n';
        }
    }
    else {
        Solve();
    }

    return 0;
}
