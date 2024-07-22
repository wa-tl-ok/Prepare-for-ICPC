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

    vector<Trio> E;

    const int no_edge = 100000;
    int n; cin >> n;

    vector<vector<long long>> M(n);
    for (int i = 0; i < n; i++) {
        M[i].resize(n);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> M[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (M[i][j] != no_edge) {
                E.push_back({ i, j, M[i][j] });
            }
        }
    }

    vector<long long> dist(n, (long long)1e18);
    vector<long long> pred(n);

    for (int k = 0; k < n; k++) {
        for (auto T : E) {
            int u = T.u;
            int v = T.v;
            long long w = T.w;

            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pred[v] = u;
            }
        }
    }

    int now = -1;

    for (auto T : E) {
        int u = T.u;
        int v = T.v;
        long long w = T.w;

        if (dist[v] > dist[u] + w) {
            now = v;
        }
    }

    if (now == -1) {
        cout << "NO";
        return 0;
    }

    cout << "YES" << "\n";

    vector<int> vis(n, false);

    while (vis[now] == false) {
        vis[now] = true;
        now = pred[now];
    }

    for (int i = 0; i < n; i++) {
        vis[i] = false;
    }
    vector<int> ans = { now };

    while (vis[now] == false) {
        vis[now] = true;
        now = pred[now];
        ans.push_back(now);
    }

    reverse(ans.begin(), ans.end());

    cout << ans.size() << "\n";
    for (auto q : ans) {
        cout << q + 1 << ' ';
    }

    return 0;
}
