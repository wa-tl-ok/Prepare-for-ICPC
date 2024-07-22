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

    vector<bool> vis(n, false);

    vector<long long> W(n, (long long)1e18);
    W[0] = 0;

    long long ans = 0;
    int components = n + 1;

    for (int i = 0; i < n; i++) {
        int u = -1;
        for (int v = 0; v < n; v++) {
            if (!vis[v]) {
                if (u == -1) {
                    u = v;
                }
                else {
                    if (W[v] < W[u]) {
                        u = v;
                    }
                }
            }
        }

        if (W[u] == (long long)1e18) {
            break;
        }

        vis[u] = true;
        ans += W[u];
        --components;

        for (auto P : G[u]) {
            int v = P.first;
            long long w = P.second;

            if (!vis[v]) {
                if (w < W[v]) {
                    W[v] = w;
                }
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
