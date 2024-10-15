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
    string ans = "Yes";

    set<char> F = { 'H', 'D','C', 'S'};
    set<char> S = { 'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
    map<string, int> M;

    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        if (F.find(s[0]) == F.end() || S.find(s[1]) == S.end()) {
            ans = "No";
        }
        M[s] += 1;
        if (M[s] == 2) {
            ans = "No";
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
