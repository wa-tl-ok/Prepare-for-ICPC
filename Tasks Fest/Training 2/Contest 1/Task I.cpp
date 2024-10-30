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
    int n; cin >> n; 
    int mx = 0;
    unordered_set<int> s;
    for (int i = 0; i < n; i++) {
        int p; cin >> p;
        mx = max(mx, p);
        s.insert(p);
    }
    vector<int> nearest(mx * 2 + 1);
    int now = 0;
    for (int i = 0; i < nearest.size(); i++) {
        nearest[i] = now;
        if (s.find(i) != s.end()) {
            now = i;
        }
    }
    int ans = 0;
    for (auto aj : s) {
        for (int x = aj * 2; x <= mx * 2; x += aj) {
            int ai = nearest[x];
            ans = max(ans, ai % aj);
        }
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
