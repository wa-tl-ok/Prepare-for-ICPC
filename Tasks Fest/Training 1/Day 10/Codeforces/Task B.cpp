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
    int x, y; cin >> x >> y;
    deque<int> ans = { x };
    
    int now = x;
    while (now != y) {
        now -= 1;
        if (now != y) {
            ans.push_front(now);
            ans.push_back(now);
        }
    }

    ans.push_back(y);

    cout << ans.size() << '\n';
    for (auto p : ans) {
        cout << p << ' ';
    } cout << '\n';
}

int main() {
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
