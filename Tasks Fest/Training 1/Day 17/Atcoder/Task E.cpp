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

void Solve() {
    int n, m, k;
    cin >> n >> m >> k;

    vector<int> U(m);
    vector<int> V(m);
    vector<int> A(m);

    for (int i = 0; i < m; i++) {
        cin >> U[i];
        cin >> V[i];
        cin >> A[i];
    }

    set<int> S;
    for (int i = 0; i < k; i++) {
        int s; cin >> s;
        --s;
        S.insert(s);
    }

    int move = n;
    n *= 2;

    vector<vector<pair<int, long long>>> G(n);
    for (int i = 0; i < m; i++) {
        int u, v, a;

        u = U[i];
        v = V[i];
        a = A[i];

        --u;
        --v;

        if (a == 1) {
            G[u].push_back({ v, 1 });
            G[v].push_back({ u, 1 });
        }
        else {
            G[u + move].push_back({ v + move, 1 });
            G[v + move].push_back({ u + move, 1 });
        }
    }

    for (auto u : S) {
        G[u].push_back({ u + move, 0 });
        G[u + move].push_back({ u, 0 });
    }

    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> Q;
    vector<long long> dist(n, (long long)9e18);
    vector<bool> vis(n, false);

    dist[0] = 0;
    Q.push({ 0, 0 });

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

    if (dist[move - 1] != (long long)9e18 || dist[n - 1] != (long long)9e18) {
        cout << min(dist[move - 1], dist[n - 1]);
    }
    else {
        cout << -1;
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
