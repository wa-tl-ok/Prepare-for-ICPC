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

class FenwickTree {
public:
    FenwickTree(int n) : size(n) {
        tree.resize(n + 1, 0);
    }

    void plus(int ind, long long x) {
        ++ind;
        while (ind <= size) {
            tree[ind] += x;
            ind += ind & -ind;
        }
    }

    void change(int ind, long long x) {
        ++ind;
        x = x - tree[ind];
        while (ind <= size) {
            tree[ind] += x;
            ind += ind & -ind;
        }
    }

    long long query(int ind) const {
        long long sum = 0;

        while (ind > 0) {
            sum += tree[ind];
            ind -= ind & -ind;
        }

        return sum;
    }

    long long range_query(int l, int r) const {
        ++l;
        ++r;
        return query(r) - query(l - 1);
    }
private:
    vector<long long> tree;
    int size;
};

void Solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int ans = 0;
    FenwickTree st_pref(n + 1);
    for (int l = 0; l < n; l++) {
        FenwickTree st_suff(n + 1);
        for (int r = n - 1; r > l; r--) {
            ans += st_pref.range_query(0, a[r] - 1) * st_suff.range_query(0, a[l] - 1);
            st_suff.plus(a[r], 1);
        }
        st_pref.plus(a[l], 1);
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
