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
    string s; cin >> s;
    int a, b; cin >> a >> b;

    string ss = "";
    for (int i = 0; i < s.size(); i++) {
        if (s[i] != '?') {
            ss += s[i];
        }
    }

    s = ss;

    if (s.size() == 0) {
        cout << 0;
        return;
    }

    int ans = 0;
    for (int i = 0; i < s.size() - 1; i++) {
        if (s[i] == '0' && s[i + 1] == '1') {
            ans += a;
        }
        if (s[i] == '1' && s[i + 1] == '0') {
            ans += b;
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
