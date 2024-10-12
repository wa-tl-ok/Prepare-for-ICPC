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
    string s; cin >> s;

    map<int, int> mi;
    for (int i = 0; i < 26; i++) {
        mi[i] = 0;
    }

    map<int, int> k;
    for (int i = 0; i < 26; i++) {
        k[i] = 0;
    }

    int ans = 0;

    for (int i = 0; i < s.size(); i++) {
        int p = s[i] - 'A';

        ans += i * k[p] - mi[p];

        mi[p] += (i + 1);
        k[p] += 1;
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
