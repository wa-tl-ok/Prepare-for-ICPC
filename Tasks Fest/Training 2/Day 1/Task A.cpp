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
    int n; cin >> n;

    vector<set<int>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        --u;
        --v;
        g[u].insert(v);
        g[v].insert(u);
    }

    vector<bool> vis(n, false);
    vis[0] = true;

    vector<int> a = { 0 };

    int ans = 1e9;
    int now = 0;

    while (a.size() > 0) {
        vector<int> b;
        for (int u : a) {
            bool f = false;
            for (auto v : g[u]) {
                if (vis[v] == false) {
                    vis[v] = true;
                    b.push_back(v);
                    f = true;
                    ++now;
                }
            }
            if (f == false) {
                while (g[u].size() == 1 && u != 0) {
                    int p = *g[u].begin();
                    g[u].erase(p);
                    g[p].erase(u);
                    u = p;
                    --now;
                }
            }
        }
        ans = min(ans, n - 1 - now);
        a.clear();
        for (auto p : b) {
            a.push_back(p);
        }
    }

    cout << ans << '\n';
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
