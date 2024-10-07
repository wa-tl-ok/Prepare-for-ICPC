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

int bs_rl(vector<int>& arr, int target) {
    if (arr[0] > target) {
        return -1;
    }
    int left = 0;
    int right = arr.size() - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (arr[mid] > target) {
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }
    return right;
}

int GO(vector<pair<int, int>>& vec) {
    int n = vec.size();
    vector<vector<pair<int, long long>>> G(n);

    for (int i = 1; i < n; i++) {
        G[i].push_back({ i - 1, (long long)(0) });
    }

    vector<int> x;
    for (int i = 0; i < n; i++) {
        x.push_back(vec[i].first);
    }

    for (int i = 0; i < n; i++) {
        int c = vec[i].second;
        int fx = x[i] + c;

        if (fx >= x[x.size() - 1]) {
            if (n - 1 != i) {
                G[i].push_back({ n - 1, (long long)(0) });
            }
        }
        else {
            int l = bs_rl(x, fx);
            if (l != i) {
                G[i].push_back({ l, (long long)(0) });
            }

            int r = l + 1;
            if (r != i) {
                G[i].push_back({ r, (long long)(x[r] - x[i] - c) });
            }
        }
    }

    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> Q;
    vector<long long> dist(n, (long long)1e18);
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

    long long mx = 0;

    for (auto p : dist) {
        mx = max(mx, p);
    }

    return mx;
}

void Solve() {
    int n; cin >> n;

    vector<pair<int, int>> vec;
    for (int i = 0; i < n; i++) {
        int a, c; cin >> a >> c;
        vec.push_back({ a, c });
    }
    sort(vec.begin(), vec.end());

    int S = 0;
    for (int i = 0; i < n; i++) {
        S += vec[i].second;
    }

    S += GO(vec);

    cout << S << '\n';
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
