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
    int n, k; 
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    set<int> S;
    for (auto p : a) {
        S.insert(p);
    }
    if (S.find(k) == S.end()) {
        cout << "no\n";
        return;
    }
    
    string ans = "no";
    for (int i = 0; i < n - 1; i++) {
        if (a[i] >= k && a[i + 1] >= k) {
            ans = "yes";
        }
    }
    for (int i = 0; i < n - 2; i++) {
        if (a[i] >= k && a[i + 2] >= k) {
            ans = "yes";
        } 
    }
    if (n == 1) {
        ans = "yes";
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
