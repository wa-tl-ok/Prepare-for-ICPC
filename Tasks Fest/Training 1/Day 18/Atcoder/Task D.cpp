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

int Find(int s, vector<vector<pair<int, long long>>>& G) {
    int n = (int)G.size();

    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> Q;
    vector<long long> dist(n, (long long)1e18);
    vector<bool> vis(n, false);

    dist[s] = 0;
    Q.push({ 0, s });

    while (!Q.empty()) {
        auto P = Q.top();

        long long weight = P.first;
        int u = P.second;

        Q.pop();

        if (vis[u]) {
            continue;
        }

        vis[u] = true;

        for (auto& P : G[u]) {
            int v = P.first;
            int w = P.second;

            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                Q.push({ dist[v], v });
            }
        }
    }

    if (dist[0] != (long long)1e18) {
        return dist[0];
    }
    else {
        return 1e18;
    }
}

void Solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, long long>>> G(n);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;

        --u;
        --v;

        G[u].push_back({ v, 1 });
    }

    int ans = 1e18;

    for (auto u : G[0]) {
        ans = min(ans, Find(u.first, G) + 1);
    }

    if (ans == 1e18) {
        cout << -1;
    }
    else {
        cout << ans;
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
