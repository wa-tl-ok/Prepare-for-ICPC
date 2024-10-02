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

class Sparse_table_min {
private:
    int N, K;
    vector<vector<int>> Stable;
public:
    Sparse_table_min(const vector<int>& vec) {
        this->N = (int)(vec.size());
        this->K = log2(N) + 2;

        Stable.resize(N + 1);

        for (int i = 0; i < N; i++) {
            Stable[i].resize(K + 1);
            Stable[i][0] = vec[i];
        }

        for (int j = 1; (1 << j) <= N; j++) {
            for (int i = 0; i + (1 << j) - 1 < N; i++) {
                Stable[i][j] = min(Stable[i][j - 1], Stable[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    int query(int l, int r) {
        int mn = 1e9;
        int sz = r - l + 1;

        for (int k = K; k >= 0; k--) {
            if (sz >= (1 << k)) {
                mn = min(mn, Stable[l][k]);
                sz -= 1 << k;

                l += 1 << k;
            }
        }

        return mn;
    }
};

void Solve() {
    int n, m; cin >> n >> m;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<int> c(n);
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }

    Sparse_table_min st(c);

    set<int> need;
    for (int i = 0; i < m; i++) {
        int t; cin >> t;
        need.insert(t);
    }

    vector<vector<int>> DP(n + 1);
    for (int i = 0; i <= n; i++) {
        DP[i].resize(n + 1);
    }
    int inf = 1e18;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            DP[i][j] = inf;
        }
    }
    for (int i = 0; i < *need.begin(); i++) {
        DP[i][0] = 0;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            if (need.find(i) == need.end()) {
                DP[i][j] = DP[i - 1][j];
            }
            DP[i][j] = min(DP[i][j], DP[i - 1][j - 1] + a[i - 1] + st.query(i - j, i - 1));
        }
    }

    int ans = inf;
    for (int i = m; i <= n; i++) {
        ans = min(ans, DP[n][i]);
    }
    cout << ans;
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
