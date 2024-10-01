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
    int n, m; cin >> n >> m;

    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++) {
        int p; cin >> p;
        a[i] = make_pair(p, i + 1);
    }
    sort(a.begin(), a.end());

    vector<int> pref_sum(n + 1);
    int now = 0;
    for (int i = 0; i < n; i++) {
        now += a[i].first;
        pref_sum[i + 1] = now;
    }

    int ans = 1e18; int ind = 0;
    for (int l = 1; l <= n; l++) {
        int r = l + m - 1;

        if (r > n) {
            break;
        }

        int S = (pref_sum[r] - pref_sum[l - 1]);
        int mi = a[l - 1].first;

        S -= mi * m;

        if (S <= ans) {
            ind = l;
            ans = S;
        }
    }

    for (int i = ind - 1; i < ind + m - 1; i++) {
        cout << a[i].second << ' ';
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
