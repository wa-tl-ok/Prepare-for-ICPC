//https://codeforces.com/contest/2022/problem/B

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

int MAX(vector<int> a) {
    int mx = -1e18;
    for (auto p : a) {
        mx = max(mx, p);
    }
    return mx;
}

int SUM(vector<int> a) {
    int s = 0;
    for (auto p : a) {
        s += p;
    }
    return s;
}

void Solve() {
    int n, x; cin >> n >> x;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    cout << max(MAX(a), (SUM(a) + x - 1) / x) << '\n';
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
