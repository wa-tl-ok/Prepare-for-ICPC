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
#include <iomanip>

using namespace std;

#define int long long

class Sparse_table_max {
private:
    int N, K;
    vector<vector<int>> Stable;
public:
    Sparse_table_max(const vector<int>& vec) {
        this->N = (int)(vec.size());
        this->K = log2(N) + 2;

        Stable.resize(N + 1);

        for (int i = 0; i < N; i++) {
            Stable[i].resize(K + 1);
            Stable[i][0] = vec[i];
        }

        for (int j = 1; (1 << j) <= N; j++) {
            for (int i = 0; i + (1 << j) - 1 < N; i++) {
                Stable[i][j] = max(Stable[i][j - 1], Stable[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    int query(int l, int r) {
        int mx = -1e9;
        int sz = r - l + 1;

        for (int k = K; k >= 0; k--) {
            if (sz >= (1 << k)) {
                mx = max(mx, Stable[l][k]);
                sz -= 1 << k;

                l += 1 << k;
            }
        }

        return mx;
    }
};

vector<int> ANS;

void Solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    if (n == 1) {
        ANS.push_back(0);
        return;
    }
    Sparse_table_max st(a);
    int mx = 0;
    for (int i = 1; i < n; i++) {
        mx = max(mx, st.query(0, i - 1) - a[i]);
    }
    if (mx == 0) {
        ANS.push_back(0);
        return;
    }
    vector<int> pref(60);
    pref[0] = 1;
    int now = 0;
    for (int i = 1; i < 60; i++) {
        pref[i] = pref[i - 1] + pow(2, i);
    }
    for (int i = 0; i < 60; i++) {
        if (pref[i] >= mx) {
            ANS.push_back(i + 1);
            return;
        }
    }
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

        for (auto p : ANS) {
            cout << p << '\n';
        }
    }
    else {
        Solve();
    }

    return 0;
}
