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

        G[u].push_back({ v, w });
        G[v].push_back({ u, w });
    }

    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> Q;
    vector<bool> vis(n, false);
    long long ans = 0;

    Q.push({ 0, 0 }); 
    int components = n + 1;

    while (!Q.empty()) {
        auto P = Q.top();

        long long weight = P.first;
        int u = P.second;

        Q.pop();

        if (vis[u]) {
            continue;
        }

        vis[u] = true;
        ans += weight;
        --components;

        for (auto& P : G[u]) {
            int v = P.first;
            long long w = P.second;

            if (!vis[v]) {
                Q.push({ w, v });
            }
        }
    }

    if (components == 1) {
        cout << ans;
    }
    else {
        cout << "NON-CONNECTED";
    }

    return 0;
}
