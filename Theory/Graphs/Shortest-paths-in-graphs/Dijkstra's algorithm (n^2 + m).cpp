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

    vector<long long> dist(n, (long long)1e18);
    vector<bool> vis(n, false);

    int s, f; 
    cin >> s >> f;

    --s;
    --f;

    dist[s] = 0;

    for (int i = 0; i < n; i++) {
        int v = -1;
        for (int u = 0; u < n; u++) {
            if (!vis[u]) {
                if (v == -1) {
                    v = u;
                }
                else {
                    if (dist[u] < dist[v]) {
                        v = u;
                    }
                }
            }
        }

        if (dist[v] == (long long)1e18) {
            break;
        }

        vis[v] = true;

        for (auto P : G[v]) {
            int u = P.first;
            long long w = P.second;

            if (dist[u] > dist[v] + w) {
                dist[u] = dist[v] + w;
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
