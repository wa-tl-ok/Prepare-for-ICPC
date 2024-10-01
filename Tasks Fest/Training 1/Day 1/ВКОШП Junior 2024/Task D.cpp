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

int Sum(int l, int r, vector<int>& pref) {
    ++l;
    ++r;
    return pref[r] - pref[l - 1];
}

void Solve() {
    int n, x, k; cin >> n >> x >> k;
    vector<pair<int, int>> R = { make_pair(x, 0) };
    for (int i = 0; i < n; i++) {
        int r, w; cin >> r >> w;
        R.push_back({ r, w });
    }
    sort(R.begin(), R.end());

    int ind = 0;
    for (int i = 0; i < (int)R.size(); i++) {
        if (R[i].second == 0) {
            ind = i;
        }
    }
    n = R.size();
    int ans = 0;

    vector<int> pref(n + 1);
    int pp = 0;
    for (int i = 0; i < n; i++) {
        pp += R[i].second;
        pref[i + 1] = pp;
    }

    int now_r = 0;
    for (int i = ind + 1; i < n; i++) {
        if (abs(R[i].first - x) > k) {
            break;
        }
        else {
            ans = max(ans, now_r + R[i].second);
        }

        now_r += R[i].second;
        int ost = k - (R[i].first - x) * 2;

        if (ost < 0) {
            // pass
        }
        else {
            int l = -1;
            int r = ind;

            while (l + 1 != r) {
                int m = (l + r) / 2;

                if (abs(R[m].first - x) > ost) {
                    l = m;
                }
                else {
                    r = m;
                }
            }

            ans = max(ans, now_r + Sum(r, ind, pref));
        }
    }

    int now_l = 0;
    for (int i = ind - 1; i >= 0; i--) {
        if (abs(R[i].first - x) > k) {
            break;
        }
        else {
            ans = max(ans, now_l + R[i].second);
        }

        now_l += R[i].second;
        int ost = k - (x - R[i].first) * 2;

        if (ost < 0) {
            // pass
        }
        else {
            int l = ind;
            int r = n;

            while (l + 1 != r) {
                int m = (l + r) / 2;

                if (abs(R[m].first - x) > ost) {
                    r = m;
                }
                else {
                    l = m;
                }
            }

            ans = max(ans, now_l + Sum(ind, l, pref));
        }
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
