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

void Solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<int> ans(n, -1);
    sort(a.begin(), a.end());
    for (int i = 0; i < n / 2; i++) {
        ans[i * 2] = a[i];
    }
    for (int i = 0; i < n / 2; i++) {
        ans[i * 2 + 1] = a[i + n / 2];
    }
    if (n % 2 == 1) {
        ans[n - 1] = a[n - 1];
    }
    string s = "YES";
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            if (ans[0] > ans[1] && ans[0] > ans[ans.size() - 1]) {
                // OK
            }
            else if (ans[0] < ans[1] && ans[0] < ans[ans.size() - 1]) {
                // OK
            }
            else {
                s = "NO";
            }
        }
        else if (i == n - 1) {
            if (ans[ans.size() - 1] > ans[ans.size() - 2] && ans[ans.size() - 1] > ans[0]) {
                // OK
            }
            else if (ans[ans.size() - 1] < ans[ans.size() - 2] && ans[ans.size() - 1] < ans[0]) {
                // OK
            }
            else {
                s = "NO";
            }
        }
        else {
            if (ans[i] > ans[i + 1] && ans[i] > ans[i - 1]) {
                // OK
            }
            else if (ans[i] < ans[i + 1] && ans[i] < ans[i - 1]) {
                // OK
            }
            else {
                s = "NO";
            }
        }
    }
    if (s == "YES") {
        cout << s << '\n';
        for (auto p : ans) {
            cout << p << ' ';
        } cout << '\n';
    }
    else {
        cout << s << '\n';
    }
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
