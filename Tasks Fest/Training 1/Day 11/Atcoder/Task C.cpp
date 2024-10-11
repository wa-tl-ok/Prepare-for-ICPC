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

int GO(string s) {
    int ans = 0;
    for (int i = 0; i < s.size() / 2; i++) {
        if (s[i] != s[s.size() - 1 - i]) {
            ++ans;
        }
    }
    return ans;
}

void Solve() {
    int n, a, b;
    cin >> n >> a >> b;
    string s; cin >> s;

    int ANS= 1e18;

    for (int ca = 0; ca < s.size(); ca++) {
        ANS = min(ANS, ca * a + GO(s) * b);
        string new_s = "";
        for (int i = 1; i < s.size(); i++) {
            new_s += s[i];
        } new_s += s[0];
        s = new_s;
    }

    cout << ANS;
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
