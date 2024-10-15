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

vector<vector<int>> G;
vector<int> vis;
map<vector<int>, int> M;

bool dfs(int u) {
    vis[u] = true;
    bool cur = false;
    for (auto v : G[u]) {
        if (vis[v] == false) {
            if (!M[vis]) {
                int ans = dfs(v);
                if (ans == false) {
                    M[vis] = 1;
                    cur = true;
                }
            }
            else {
                int ans = M[vis];
                if (ans == 1) {
                    cur = true;
                }
            }
        }
    }
    if (cur == false) {
        M[vis] = 2;
    }
    else {
        M[vis] = 1;
    }
    vis[u] = false;
    return cur;
}

void Solve() {
    int n; cin >> n;
    vector<string> a(n + 1);
    for (int i = 1; i <= n; i++) {
        string s; cin >> s;
        a[i] = s;
    }
    G.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i != j) {
                if (a[i][a[i].size() - 1] == a[j][0]) {
                    G[i].push_back(j);
                }
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        G[0].push_back(i);
    }
    vis.resize(n + 1);
    for (int i = 0; i < n + 1; i++) {
        vis[i] = false;
    }
    if (dfs(0) == true) {
        cout << "First";
    }
    else {
        cout << "Second";
    }
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
