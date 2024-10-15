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
    int x, k; cin >> x >> k;

    if (k > to_string(x).size()) {
        cout << 0;
        return;
    }

    string s = to_string(x);
    int pos = s.size() - 1;
    int f = 0;

    string ans = "";
    int i = 1;

    while (pos >= 0) {
        if (i <= k) {
            if (s[pos] + f >= '5') {
                f = 1;
                ans += "0";
            }
            else {
                f = 0;
                ans += "0";
            }
        }
        else {
            if (s[pos] + f <= '9') {
                ans += (char)(s[pos] + f);
                f = 0;
            }
            else {
                ans += "0";
                f = 1;
            }
        }

        --pos; ++i;
    }

    if (f == 1) {
        ans += "1";
    }

    reverse(ans.begin(), ans.end());

    bool g = false;
    for (int i = 0; i < ans.size(); i++) {
        if (ans[i] != '0') {
            g = true;
        }
    }

    if (g == true) {
        cout << ans;
    }
    else {
        cout << 0;
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
