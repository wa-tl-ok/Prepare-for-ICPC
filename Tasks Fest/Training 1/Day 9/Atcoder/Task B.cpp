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
    int m; cin >> m;

    vector<string> S;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        S.push_back(s);
    }

    vector<string> T;
    for (int i = 0; i < m; i++) {
        string s; cin >> s;
        T.push_back(s);
    }

    int ans = 0;

    for (int i = 0; i < n; i++) {
        string s = S[i];

        for (auto t : T) {
            if (t[0] == s[3] && t[1] == s[4] && t[2] == s[5]) {
                ++ans;
                break;
            }
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
