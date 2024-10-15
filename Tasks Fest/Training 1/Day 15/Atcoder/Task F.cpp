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
    int x; cin >> x;

    vector<vector<vector<int>>> DP;
    DP.resize(3005);
    for (int i = 0; i < 3005; i++) {
        DP[i].resize(3005);
    }
    for (int i = 0; i < 3005; i++) {
        for (int j = 0; j < 3005; j++) {
            DP[i][j].resize(2);
        }
    }
    for (int i = 0; i < 3005; i++) {
        for (int j = 0; j < 3005; j++) {
            for (int k = 0; k < 2; k++) {
                DP[i][j][k] = 1e18;
            }
        }
    }
    DP[0][0][0] = 0;
    DP[0][0][1] = 0;

    vector<int> y(n);
    vector<int> z(n);
    map<int, int> k;
    for (int i = 0; i < n; i++) {
        cin >> y[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> z[i];
        k[y[i]] = z[i];
    }

    vector<pair<int, int>> events_right = { { 0, 2 } };
    vector<pair<int, int>> events_left = { { 0, 2 } };
    for (int i = 0; i < n; i++) {
        if (y[i] < 0) { events_left.push_back(make_pair(y[i], 0)); }
        else { events_right.push_back(make_pair(y[i], 0)); }
        if (z[i] < 0) { events_left.push_back(make_pair(z[i], 1)); }
        else { events_right.push_back(make_pair(z[i], 1)); }
    }
    if (x >= 0) { events_right.push_back(make_pair(x, 3)); }
    if (x <= 0) { events_left.push_back(make_pair(x, 3)); }

    sort(events_right.begin(), events_right.end());
    sort(events_left.begin(), events_left.end());
    reverse(events_left.begin(), events_left.end());

    int ans = 1e18;

    for (int L = 0; L < events_left.size(); L++) {
        for (int R = 0; R < events_right.size(); R++) {
            if (L + 1 < events_left.size()) {
                if (events_left[L + 1].second == 1) {
                    DP[L + 1][R][0] = min(DP[L + 1][R][0], DP[L][R][0] + abs(events_left[L + 1].first - events_left[L].first));
                    DP[L + 1][R][0] = min(DP[L + 1][R][0], DP[L][R][1] + abs(events_left[L + 1].first - events_right[R].first));
                }
                else if (events_left[L + 1].second == 2) {
                    DP[L + 1][R][0] = min(DP[L + 1][R][0], DP[L][R][0] + abs(events_left[L + 1].first - events_left[L].first));
                    DP[L + 1][R][0] = min(DP[L + 1][R][0], DP[L][R][1] + abs(events_left[L + 1].first - events_right[R].first));
                }
                else if (events_left[L + 1].second == 3) {
                    DP[L + 1][R][0] = min(DP[L + 1][R][0], DP[L][R][0] + abs(events_left[L + 1].first - events_left[L].first));
                    DP[L + 1][R][0] = min(DP[L + 1][R][0], DP[L][R][1] + abs(events_left[L + 1].first - events_right[R].first));

                    ans = min(ans, DP[L + 1][R][0]);
                }
                else if (events_left[L + 1].second == 0) {
                    int cx = events_left[L + 1].first;
                    int key_cx = k[cx];

                    bool F = false;
                    if (key_cx < 0) {
                        if (events_left[L + 1].first <= key_cx) {
                            F = true;
                        }
                    }
                    else {
                        if (events_right[R].first >= key_cx) {
                            F = true;
                        }
                    }

                    if (F == true) {
                        DP[L + 1][R][0] = min(DP[L + 1][R][0], DP[L][R][0] + abs(events_left[L + 1].first - events_left[L].first));
                        DP[L + 1][R][0] = min(DP[L + 1][R][0], DP[L][R][1] + abs(events_left[L + 1].first - events_right[R].first));
                    }
                }
            }

            if (R + 1 < events_right.size()) {
                if (events_right[R + 1].second == 1) {
                    DP[L][R + 1][1] = min(DP[L][R + 1][1], DP[L][R][0] + abs(events_right[R + 1].first - events_left[L].first));
                    DP[L][R + 1][1] = min(DP[L][R + 1][1], DP[L][R][1] + abs(events_right[R + 1].first - events_right[R].first));
                }
                else if (events_right[R + 1].second == 2) {
                    DP[L][R + 1][1] = min(DP[L][R + 1][1], DP[L][R][0] + abs(events_right[R + 1].first - events_left[L].first));
                    DP[L][R + 1][1] = min(DP[L][R + 1][1], DP[L][R][1] + abs(events_right[R + 1].first - events_right[R].first));
                }
                else if (events_right[R + 1].second == 3) {
                    DP[L][R + 1][1] = min(DP[L][R + 1][1], DP[L][R][0] + abs(events_right[R + 1].first - events_left[L].first));
                    DP[L][R + 1][1] = min(DP[L][R + 1][1], DP[L][R][1] + abs(events_right[R + 1].first - events_right[R].first));

                    ans = min(ans, DP[L][R + 1][1]);
                }
                else if (events_right[R + 1].second == 0) {
                    int cx = events_right[R + 1].first;
                    int key_cx = k[cx];

                    bool F = false;
                    if (key_cx < 0) {
                        if (events_left[L].first <= key_cx) {
                            F = true;
                        }
                    }
                    else {
                        if (events_right[R + 1].first >= key_cx) {
                            F = true;
                        }
                    }

                    if (F == true) {
                        DP[L][R + 1][1] = min(DP[L][R + 1][1], DP[L][R][0] + abs(events_right[R + 1].first - events_left[L].first));
                        DP[L][R + 1][1] = min(DP[L][R + 1][1], DP[L][R][1] + abs(events_right[R + 1].first - events_right[R].first));
                    }
                }
            }

            //cout << "DEBUG -----> " << "L = " << L << ", " << "R = " << R << " -----> " << 
            //    "DP[L][R][0] = " << DP[L][R][0] << " and " << "DP[L][R][1] = " << DP[L][R][1] << '\n';
        }
    }

    if (ans != 1e18) {
        cout << ans;
    }
    else {
        cout << -1;
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
