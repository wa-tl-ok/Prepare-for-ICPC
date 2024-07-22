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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, long long>>> G(n);

    for (int i = 0; i < m; i++) {
        int u, v; long long w;
        cin >> u >> v >> w;

        --u;
        --v;

        G[u].push_back({ v, w });
    }

    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> Q;
    vector<long long> dist(n, (long long)1e18);
    vector<bool> vis(n, false);

    int s, f;
    cin >> s >> f;

    --s;
    --f;

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
            long long w = P.second;

            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                Q.push({ dist[v], v });
            }
        }
    }

    if (dist[f] != (long long)1e18) {
        cout << dist[f];
    }
    else {
        cout << -1;
    }

    return 0;
}
