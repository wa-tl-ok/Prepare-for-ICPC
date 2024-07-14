//https://atcoder.jp/contests/abc361/tasks/abc361_e

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
#include <random>

using namespace std;

int Get(vector<vector<pair<int, long long>>>& G, int s) {
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
            long long w = P.second;

            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                Q.push({ dist[v], v });
            }
        }
    }

    int v = -1;
    long long mx_dist = -1;

    for (int i = 0; i < n; i++) {
        if (dist[i] > mx_dist) {
            mx_dist = dist[i];
            v = i;
        }
    }

    return v;
}

long long Find(vector<vector<pair<int, long long>>>& G, int s, int f) {
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
            long long w = P.second;

            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                Q.push({ dist[v], v });
            }
        }
    }

    return dist[f];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n; cin >> n;
    long long S = 0;

    vector<vector<pair<int, long long>>> G(n);

    for (int i = 0; i < n - 1; i++) {
        int a, b; long long c; 
        cin >> a >> b >> c;

        int u = a - 1;
        int v = b - 1;
        long long w = c;

        G[u].push_back({ v, w });
        G[v].push_back({ u, w });

        S += c;
    }

    int u = Get(G, 0);
    int v = Get(G, u);

    long long D = Find(G, u, v);

    cout << S * 2 - D;

    return 0;
}
