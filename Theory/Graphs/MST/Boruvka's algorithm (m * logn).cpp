#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>
#include <deque>
#include <array>
#include <list>
#include <stack>
#include <tuple>
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
    int components;

    DSU(int n) {
        head.resize(n);
        for (int i = 0; i < n; i++) {
            head[i] = i;
        }

        rang.resize(n);
        for (int i = 0; i < n; i++) {
            rang[i] = 1;
        }

        components = n;
    }

    int Find(int x) {
        if (head[x] == x) {
            return x;
        }
        return head[x] = Find(head[x]);
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

        head[x] = y;

        if (rang[x] == rang[y]) {
            ++rang[y];
        }

        --components;

        return true;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    vector<tuple<int, int, long long>> edges(m);

    for (int i = 0; i < m; ++i) {
        int u, v; long long w;
        cin >> u >> v >> w;

        edges[i] = { w, u, v };
    }

    DSU dsu(n);
    long long ans = 0;

    while (dsu.components > 1) {
        vector<int> cheapest(n, -1);
        bool Flag = false;

        for (int i = 0; i < m; ++i) {
            long long w = get<0>(edges[i]);
            int u = get<1>(edges[i]);
            int v = get<2>(edges[i]);

            int set_u = dsu.Find(u);
            int set_v = dsu.Find(v);

            if (set_u != set_v) {
                if (cheapest[set_u] == -1 || get<0>(edges[cheapest[set_u]]) > w) {
                    cheapest[set_u] = i;
                }
                if (cheapest[set_v] == -1 || get<0>(edges[cheapest[set_v]]) > w) {
                    cheapest[set_v] = i;
                }
            }
        }

        for (int i = 0; i < n; ++i) {
            if (cheapest[i] != -1) {
                long long w = get<0>(edges[cheapest[i]]);
                int u = get<1>(edges[cheapest[i]]);
                int v = get<2>(edges[cheapest[i]]);

                if (dsu.Union(u, v)) {
                    ans += w;
                    Flag = true;
                }
            }
        }

        if (Flag == false) {
            break;
        }
    }

    if (dsu.components == 1) {
        cout << ans;
    }
    else {
        cout << "NON-CONNECTED";
    }

    return 0;
}
