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

int F(int n, int m) {
    int ans = 0;
    while (n % m == 0) {
        n /= m;
        ++ans;
    }
    return ans;
}

int Go(int n, int p) {
    int plus = n;
    while (p > 0) {
        p -= F(n, plus);
        n += plus;
    }
    return n - plus;
}

void Solve() {
    int k; cin >> k;
    map<int, int> M;
    for (int i = 2; i * i <= k; i++) {
        while (k % i == 0) {
            k /= i;
            M[i] += 1;
        }
    }
    if (k != 1) {
        M[k] = 1;
    }

    int ans = 0;
    for (auto P : M) {
        ans = max(ans, Go(P.first, P.second));
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
