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
    int n, k; cin >> n >> k;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    Sparse_table_min st(a);

    vector<vector<int>> DP(n + 1);
    for (int i = 0; i < n + 1; i++) {
        DP[i].resize(k + 1);
    }
    for (int i = 0; i < n + 1; i++) {
        for (int j = 0; j < k + 1; j++) {
            DP[i][j] = 1e18;
        }
    }
    DP[0][0] = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= k; j++) {
            for (int p = 0; i + p + 1 <= n && j + p <= k; p++) {
                int mn = st.query(i, i + p);
                DP[i + p + 1][j + p] = min(DP[i + p + 1][j + p], DP[i][j] + mn * (p + 1));
            }
        }
    }

    int ans = 1e18;
    for (int i = 0; i <= k; i++) {
        ans = min(ans, DP[n][i]);
    }
    cout << ans << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int multitest = true;
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
