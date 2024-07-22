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

    struct Trio {
        int u;
        int v;
        long long w;
    };

    int n, m;
    cin >> n >> m;

    vector<Trio> E;

    for (int i = 0; i < m; i++) {
        int u, v; long long w;
        cin >> u >> v >> w;

        --u;
        --v;

        E.push_back({ u, v, w });
    }

    vector<long long> dist(n, (long long)1e18);

    int s, f;
    cin >> s >> f;

    --s;
    --f;

    dist[s] = 0;

    for (int k = 0; k < n; k++) {
        for (auto T : E) {
            int u = T.u;
            int v = T.v;
            long long w = T.w;

            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
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
