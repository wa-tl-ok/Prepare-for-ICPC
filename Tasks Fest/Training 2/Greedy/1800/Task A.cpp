//https://codeforces.com/contest/1935/problem/C

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

void Solve() {
    int n, mx; cin >> n >> mx;
    vector<pair<int, int>> v;
    for (int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;
        v.push_back(make_pair(b, a));
    }
    sort(v.begin(), v.end());

    if (n == 1) {
        if (v[0].second <= mx) {
            cout << 1 << '\n';
        }
        else {
            cout << 0 << '\n';
        }
        return;
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        multiset<int> a;
        int cur = 0;
        for (int j = i; j < n; j++) {
            a.insert(v[j].second);
            cur += v[j].second;
            while (a.size() > 0 && cur + v[j].first - v[i].first > mx) {
                auto it = a.end(); --it; cur -= (*it); a.erase(it);
            }
            ans = max(ans, (int)a.size());
        }
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
