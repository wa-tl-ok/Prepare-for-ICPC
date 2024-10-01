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
    int a, b, c;
    cin >> a >> b >> c;

    int ans = a;

    ans += b / 3;
    b %= 3;

    if (b == 0) {
        ans += (c + 3 - 1) / 3;
    }
    else if (b == 1) {
        if (c == 0 || c == 1) {
            ans = -1;
        }
        else {
            ans += (c + b + 3 - 1) / 3;
        }
    }
    else {
        if (c == 0) {
            ans = -1;
        }
        else {
            ans += (c + b + 3 - 1) / 3;
        }
    }

    cout << ans;
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
