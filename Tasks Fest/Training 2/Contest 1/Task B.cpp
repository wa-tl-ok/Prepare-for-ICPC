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
    string s; cin >> s;
    string g = "";
    for (int i = 0; i < n; i++) {
        if (s[i] != '0' && s[i] != '1') {
            g += s[i];
        }
    }
    vector<char> ans;
    for (int i = 0; i < g.size(); i++) {
        if (g[i] == '4') {
            ans.push_back({ '3' });
            ans.push_back({ '2' });
            ans.push_back({ '2' });
        }
        else if (g[i] == '6') {
            ans.push_back({ '5' });
            ans.push_back({ '3' });
        }
        else if (g[i] == '8') {
            ans.push_back({ '7' });
            ans.push_back({ '2' });
            ans.push_back({ '2' });
            ans.push_back({ '2' });
        }
        else if (g[i] == '9') {
            ans.push_back({ '7' });
            ans.push_back({ '3' });
            ans.push_back({ '3' });
            ans.push_back({ '2' });
        }
        else {
            ans.push_back({ g[i]});
        }
    }
    sort(ans.begin(), ans.end());
    reverse(ans.begin(), ans.end());
    for (auto p : ans) {
        cout << p;
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
