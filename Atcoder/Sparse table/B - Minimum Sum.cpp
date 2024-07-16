//https://atcoder.jp/contests/agc005/tasks/agc005_b

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

class Sparse_table {
private:
    int N, K; 
    vector<vector<int>> Stable;
public:
    Sparse_table(const vector<int>& vec) {
        this -> N = (int)(vec.size());
        this -> K = log2(N) + 2;

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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n; cin >> n;
    long long ans = 0;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    Sparse_table st(a); 

    for (int i = 0; i < n; i++) {
        int l, r, L, R;

        // Left find start

        l = 0, r = i, L = i;

        while (l <= r) {
            int m = (l + r) / 2;

            if (st.query(m, i) == a[i]) {
                r = m - 1;
            }
            else {
                l = m + 1;
            }
        }

        L = l;

        // Left find end



        // Right find start

        l = i, r = n - 1, R = i;

        while (l <= r) {
            int m = (l + r) / 2;

            if (st.query(i, m) == a[i]) {
                l = m + 1;
            }
            else {
                r = m - 1;
            }
        }

        R = r;

        // Right find end



        ans += (long long)a[i] * (i - L + 1) * (R - i + 1);
    }

    cout << ans;

    return 0;
}
