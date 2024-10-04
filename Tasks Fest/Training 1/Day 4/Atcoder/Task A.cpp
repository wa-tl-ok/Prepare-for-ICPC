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

int Count(string s, char c) {
    int ans = 0;
    for (auto p : s) {
        if (p == c) {
            ans += 1;
        }
    }
    return ans;
}

void Solve() {
    int n, m; cin >> n >> m;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        ans += Count(s, '#');
    }
    cout << ans << '\n';
}

int main() {
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
