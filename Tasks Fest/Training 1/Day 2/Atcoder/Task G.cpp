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
    vector<int> w;

    DSU(vector<int> stw) {
        int n = stw.size();

        head.resize(n);
        for (int i = 0; i < n; i++) {
            head[i] = i;
        }

        rang.resize(n);
        for (int i = 0; i < n; i++) {
            rang[i] = 1;
        }

        w.resize(n);
        for (int i = 0; i < n; i++) {
            w[i] = stw[i];
        }
    }

    int Find(int x) {
        if (head[x] == x) {
            return x;
        }
        return Find(head[x]);
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
        w[y] = min(w[y], w[x]);

        if (rang[x] == rang[y]) {
            ++rang[y];
        }

        return true;
    }
};

vector<vector<int>> G;
vector<int> w;

vector<int> tin;
vector<int> tout;
int tm = 0;

void dfs(int v) {
    tm += 1;
    tin[v] = tm;

    for (auto u : G[v]) {
        dfs(u);

        w[v] = min(w[v], w[u]);
    }

    tm += 1;
    tout[v] = tm;
}

void Solve() {
    vector<int> ANS;

    int n; cin >> n;

    G.resize(n);
    vector<int> p(n, -1);
    for (int i = 1; i < n; i++) {
        cin >> p[i];

        int u = p[i];
        int v = i + 1;

        --u;
        --v;

        --p[i];

        G[u].push_back(v);
    }

    w.resize(n);
    for (int i = 0; i < n; i++) {
        w[i] = i;
    }

    tin.resize(n);
    tout.resize(n);

    dfs(0);

    DSU dsu(w);

    int q; cin >> q;
    for (int i = 0; i < q; i++) {
        int t; cin >> t;
        if (t == 1) {
            int u, v; cin >> u >> v;

            --u;
            --v;

            while (u > v) {
                int pred_u = dsu.w[dsu.Find(p[u])];
                dsu.Union(u, pred_u);
                u = pred_u;
            }
        }
        else {
            int u; cin >> u;
            ANS.push_back(dsu.w[dsu.Find(u - 1)]);
        }
    }

    for (auto ans : ANS) {
        cout << ans + 1 << '\n';
    }
}

int main() {
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
