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
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<int> b(n);
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    vector<pair<int, int>> P;
    for (int i = 0; i < n; i++) {
        P.push_back({ a[i], b[i]});
    }
    sort(P.begin(), P.end());
    multiset<int> S; int Sum = 0;
    for (int i = 0; i < k; i++) {
        S.insert(P[i].second);
        Sum += P[i].second;
    }
    int ans = P[k - 1].first * Sum;
    for (int i = k; i < n; i++) {
        auto it = S.end();
        --it;
        Sum -= (*it);
        Sum += P[i].second;
        S.erase(it);
        S.insert(P[i].second);
        ans = min(ans, Sum * P[i].first);
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
