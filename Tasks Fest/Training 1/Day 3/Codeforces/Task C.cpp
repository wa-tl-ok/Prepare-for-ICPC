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

void Solve() {
    int n; cin >> n;

    vector<vector<int>> M(n);
    for (int i = 0; i < n; i++) {
        M[i].resize(n);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            M[i][j] = 1e9;

            if (i == j) {
                M[i][j] = 0;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        string s; cin >> s;

        for (int j = 0; j < n; j++) {
            if (s[j] == '1') {
                M[i][j] = 1;
            }
        }
    }

    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            for (int k = 0; k < n; k++) {
                if (M[u][v] + M[v][k] < M[u][k]) {
                    M[u][k] = M[u][v] + M[v][k];
                }
            }
        }
    }

    int m; cin >> m;
    vector<int> nodes(m);
    for (int i = 0; i < m; i++) {
        cin >> nodes[i];
        nodes[i]--;
    }

    int last = 0;

    vector<int> ans;
    ans.push_back(nodes[0]);
    for (int i = 1; i < m; i++) {
        if (M[ans[ans.size() - 1]][nodes[i]] < i - last) {
            ans.push_back(nodes[i - 1]);
            last = i - 1;
        }
    }
    ans.push_back(nodes[nodes.size() - 1]);

    cout << ans.size() << '\n';
    for (auto p : ans) {
        cout << p + 1 << ' ';
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
