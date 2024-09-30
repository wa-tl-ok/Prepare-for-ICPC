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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, m, k; cin >> n >> m >> k;
    string s; cin >> s;

    int bad = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'x') {
            ++bad;
        }
    }

    if (k >= bad * m) {
        cout << n * m;
        return 0;
    }

    int ans = (k / bad) * n;

    m -= k / bad;
    k %= bad;

    if (m == 1) {
        string ss = s;

        vector<int> a(n, 0);
        for (int i = 0; i < n; i++) {
            if (ss[i] == 'x') {
                a[i] = 1;
            }
        }

        DST st(a);

        int mx = 0;
        for (int L = 0; L < n; L++) {
            int l = L;
            int r = n;

            while (l + 1 != r) {
                int m = (l + r) / 2;

                if (st.query(L, m) > k) {
                    r = m;
                }
                else {
                    l = m;
                }
            }

            int R = l;

            mx = max(mx, R - L + 1);
        }

        cout << ans + mx;
    }
    else if (m >= 2) {
        string ss = s + s;

        vector<int> a(2 * n, 0);
        for (int i = 0; i < 2 * n; i++) {
            if (ss[i] == 'x') {
                a[i] = 1;
            }
        }

        DST st(a);

        int mx = 0;
        for (int L = 0; L < 2 * n; L++) {
            int l = L;
            int r = 2 * n;

            while (l + 1 != r) {
                int m = (l + r) / 2;

                if (st.query(L, m) > k) {
                    r = m;
                }
                else {
                    l = m;
                }
            }

            int R = l;

            mx = max(mx, R - L + 1);
        }

        cout << ans + mx;
    }

    return 0;
}
