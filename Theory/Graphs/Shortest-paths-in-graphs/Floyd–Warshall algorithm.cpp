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

    vector<vector<long long>> M(n);
    for (int i = 0; i < n; i++) {
        M[i].resize(n);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                M[i][j] = 0;
            }
            else {
                M[i][j] = (long long)1e18;
            }
        }
    }

    for (int i = 0; i < m; i++) {
        int u, v; long long w;
        cin >> u >> v >> w;

        --u;
        --v;

        M[u][v] = w;
    }

    int s, f;
    cin >> s >> f;

    --s;
    --f;

    for (int v = 0; v < n; v++) {
        for (int u = 0; u < n; u++) {
            for (int k = 0; k < n; k++) {
                if (M[u][v] + M[v][k] < M[u][k]) {
                    M[u][k] = M[u][v] + M[v][k];
                }
            }
        }
    }

    if (M[s][f] != (long long)1e18) {
        cout << M[s][f];
    }
    else {
        cout << -1;
    }

    return 0;
}
