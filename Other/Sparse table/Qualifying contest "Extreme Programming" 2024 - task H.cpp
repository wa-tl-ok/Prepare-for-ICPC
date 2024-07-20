#include <iostream> 
#include <iomanip> 
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
#include <random> 

using namespace std;

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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, x, y; cin >> n >> x >> y;
    long long ans = 0;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    Sparse_table_min mn(a);
    Sparse_table_max mx(a);

    for (int i = 0; i < n; i++) {
        int l, r;
        int l1, l2;
        int r1, r2;
        bool F1, F2;

        if (a[i] > x || a[i] < y) {
            // do nothing
        }
        else {
            if (mx.query(i, n - 1) < x || mn.query(i, n - 1) > y) {
                // do nothing
            }
            else {
                l = i - 1, r = n; F1 = false;

                while (l + 1 != r) {
                    int m = (l + r) / 2;

                    if (mx.query(i, m) < x) {
                        l = m;
                    }
                    else if (mx.query(i, m) == x) {
                        r = m;
                        F1 = true;
                    }
                    else {
                        r = m;
                    }
                }

                l1 = r;

                l = i - 1, r = n; F2 = false;

                while (l + 1 != r) {
                    int m = (l + r) / 2;

                    if (mn.query(i, m) > y) {
                        l = m;
                    }
                    else if (mn.query(i, m) == y) {
                        r = m;
                        F2 = true;
                    }
                    else {
                        r = m;
                    }
                }

                l2 = r;

                l = i - 1, r = n; F1 = false;

                while (l + 1 != r) {
                    int m = (l + r) / 2;

                    if (mx.query(i, m) < x) {
                        l = m;
                    }
                    else if (mx.query(i, m) == x) {
                        l = m;
                        F1 = true;
                    }
                    else {
                        r = m;
                    }
                }

                r1 = r;

                l = i - 1, r = n; F2 = false;

                while (l + 1 != r) {
                    int m = (l + r) / 2;

                    if (mn.query(i, m) > y) {
                        l = m;
                    }
                    else if (mn.query(i, m) == y) {
                        l = m;
                        F2 = true;
                    }
                    else {
                        r = m;
                    }
                }

                r2 = r;

                if (F1 == true && F2 == true) {
                    ans += (long long)max(0, min(r1, r2) - max(l1, l2));
                }
            }
        }
    }

    cout << ans;

    return 0;
}
