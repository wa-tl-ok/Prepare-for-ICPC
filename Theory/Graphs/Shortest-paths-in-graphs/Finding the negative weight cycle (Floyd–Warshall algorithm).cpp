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

    vector<vector<long long>> Next(n);
    for (int i = 0; i < n; i++) {
        Next[i].resize(n);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (M[i][j] != no_edge) {
                Next[i][j] = j;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int u = 0; u < n; u++) {
            for (int v = 0; v < n; v++) {
                if (M[u][i] != no_edge && M[i][v] != no_edge && M[u][v] > M[u][i] + M[i][v]) {
                    M[u][v] = M[u][i] + M[i][v];
                    Next[u][v] = Next[u][i];

                    if (M[u][v] < 0 && u == v) {
                        cout << "YES" << "\n";

                        vector<int> ans;

                        int now = u;
                        int finish = u;

                        ans.push_back(now);
                        now = Next[now][finish];

                        while (now != finish) {
                            ans.push_back(now);
                            now = Next[now][finish];
                        }

                        ans.push_back(now);
                        now = Next[now][finish];

                        cout << ans.size() << "\n";
                        for (auto q : ans) {
                            cout << q + 1 << ' ';
                        }

                        return 0;
                    }
                }
            }
        }
    }

    cout << "NO";

    return 0;
}
