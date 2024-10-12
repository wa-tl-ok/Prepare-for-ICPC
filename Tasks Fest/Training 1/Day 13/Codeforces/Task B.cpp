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

class DST {
private:
    int N, K;

    vector<vector<int>> Stable;
    vector<int> highestBit;
    vector<int> a;

    int Function(int left, int right) {
        return (left + right);
    }
public:
    DST(const vector<int>& vec) {
        for (auto p : vec) {
            a.push_back(p);
        }

        this->K = 0;

        int n = (int)vec.size();
        int p = 1;
        while (p < n) {
            p <<= 1;
            ++(this->K);
        }

        for (int i = 0; i < p - n; i++) {
            a.push_back(1);
        }

        this->N = (int)a.size();

        highestBit.resize(N);
        highestBit[0] = 0;
        highestBit[1] = 0;
        for (int i = 2; i < N; i++) {
            highestBit[i] = highestBit[i >> 1] + 1;
        }

        Stable.resize(N);
        for (int i = 0; i < N; i++) {
            Stable[i].resize(K);
            Stable[i][0] = a[i];
        }

        int sz = 1;
        for (int lvl = 1; lvl < K; lvl++) {
            sz = sz <<= 1;
            for (int c = sz; c < N; c += sz << 1) {
                Stable[c][lvl] = a[c];
                for (int i = c + 1; i < c + sz; i++) {
                    Stable[i][lvl] = Function(a[i], Stable[i - 1][lvl]);
                }

                Stable[c - 1][lvl] = a[c - 1];
                for (int i = c - 2; i >= c - sz; i--) {
                    Stable[i][lvl] = Function(a[i], Stable[i + 1][lvl]);
                }
            }
        }
    }

    int query(int left, int right) {
        if (left == right) {
            return a[left];
        }
        else {
            int lvl = highestBit[left ^ right];
            return Function(Stable[left][lvl], Stable[right][lvl]);
        }
    }
};

void Solve() {
    int n, q, k; cin >> n >> q >> k;

    vector<int> a(n + 2);
    a[0] = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    a[n + 1] = k;

    vector<int> p(n + 2);
    for (int i = 1; i <= n; i++) {
        p[i] = a[i + 1] - a[i - 1] - 1;
    }

    DST dst(p);

    for (int i = 0; i < q; i++) {
        int l, r; cin >> l >> r;
        
        if (l == r) {
            cout << k - 1 << '\n';
        }
        else {
            int ans = (a[l + 1] - 1) + (k - a[r - 1]);

            ++l;
            --r;
            if (l <= r) {
                ans += dst.query(l, r);
            }

            --l;
            ++r;
            ans -= (r - l + 1);

            cout << ans << '\n';
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
