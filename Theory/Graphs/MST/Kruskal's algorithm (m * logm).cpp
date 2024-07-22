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

    struct Trio {
        int u;
        int v;
        long long w;

        bool operator <(const Trio& other) {
            return w < other.w;
        }
    };

    int n, m; cin >> n >> m;
    vector<Trio> edges;

    for (int i = 0; i < m; i++) {
        int u, v; long long w; cin >> u >> v >> w;

        Trio T;
        T.u = u;
        T.v = v;
        T.w = w;

        edges.push_back(T);
    }

    sort(edges.begin(), edges.end());

    DSU dsu(n); long long ans = 0;

    for (int i = 0; i < m; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        long long w = edges[i].w;

        if (dsu.Union(u, v)) {
            ans += w;
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
