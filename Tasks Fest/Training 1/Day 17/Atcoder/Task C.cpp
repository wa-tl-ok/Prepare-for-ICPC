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

map<int, vector<int>> G;
map<int, int> vis;
int mx = 1;

void dfs(int u) {
    mx = max(mx, u);
    vis[u] = 1;
    for (auto v : G[u]) {
        if (vis[v] == 1) {
            continue;
        }
        dfs(v);
    }
}

void Solve() {
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    dfs(1);
    cout << mx;
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
