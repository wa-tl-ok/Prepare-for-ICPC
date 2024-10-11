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
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

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
                M[i][j] = n;
            }
        }
    }

    vector<vector<long long>> S(n);
    for (int i = 0; i < n; i++) {
        S[i].resize(n);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            S[i][j] = 0;
        }
    }

    for (int i = 0; i < n; i++) {
        string s; cin >> s;

        for (int j = 0; j < n; j++) {
            if (s[j] == 'Y') {
                if (i != j) {
                    M[i][j] = 1;
                    S[i][j] = a[i];
                }
            }
        }
    }

    for (int v = 0; v < n; v++) {
        for (int u = 0; u < n; u++) {
            for (int k = 0; k < n; k++) {
                if (M[u][v] + M[v][k] < M[u][k]) {
                    M[u][k] = M[u][v] + M[v][k];
                    S[u][k] = S[u][v] + S[v][k];
                }
                else if (M[u][v] + M[v][k] == M[u][k]) {
                    S[u][k] = max(S[u][k], S[u][v] + S[v][k]);
                }
            }
        }
    }

    int q; cin >> q;
    for (int i = 0; i < q; i++) {
        int u, v; cin >> u >> v;
        --u;
        --v;
        if (M[u][v] != n) {
            cout << M[u][v] << ' ' << S[u][v] + a[v] << '\n';
        }
        else {
            cout << "Impossible" << '\n';
        }
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
