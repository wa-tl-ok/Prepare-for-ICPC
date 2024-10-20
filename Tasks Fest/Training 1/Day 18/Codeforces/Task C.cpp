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
    int n; cin >> n;
    string s; cin >> s;
    if (s[0] == '1' || s[s.size() - 1] == '1') {
        cout << "YES\n";
        return;
    }
    else {
        for (int i = 0; i < n - 1; i++) {
            if (s[i] == '1' && s[i + 1] == '1') {
                cout << "YES\n";
                return;
            }
        }
    }
    cout << "NO\n";
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
