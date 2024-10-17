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
    int n, k; cin >> n >> k;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    sort(a.begin(), a.end());

    map<int, vector<int>> m;
    for (int i = 0; i < n; i++) {
        m[a[i] % k].push_back(a[i]);
    }

    int f = 0;
    for (auto p : m) {
        f += p.second.size() % 2;
    }

    if (f >= 2) {
        cout << -1 << '\n';
        return;
    }

    int ans = 0;

    for (auto p : m) {
        vector<int> v = p.second;

        if (v.size() % 2 == 0) {
            for (int i = 0; i < v.size(); i += 2) {
                ans += (v[i + 1] - v[i]) / k;
            }
        }
        else {
            if (v.size() == 1) {
                continue;
            }

            int mn = 1e18;

            vector<int> pref(v.size() / 2);
            int now_pref = 0; int cp = 0;
            for (int i = 0; i < v.size() - 1; i += 2) {
                now_pref += v[i + 1] - v[i];
                pref[cp] = now_pref;
                ++cp;
            }

            mn = min(mn, now_pref);

            vector<int> suff(v.size() / 2);
            int now_suff = 0; int cf = v.size() / 2 - 1;
            for (int i = v.size() - 1; i > 0; i -= 2) {
                now_suff += v[i] - v[i - 1];
                suff[cf] = now_suff;
                --cf;
            }

            mn = min(mn, now_suff);

            for (int i = 0; i < v.size() / 2 - 1; i++) {
                mn = min(mn, pref[i] + suff[i + 1]);
            }

            ans += mn / k;
        }
    }

    cout << ans << '\n';
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
