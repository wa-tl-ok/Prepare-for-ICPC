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

int Max(vector<int> a) {
    int ans = 0;
    for (auto p : a) {
        ans = max(ans, p);
    }
    return ans;
}

int Min(vector<int> a) {
    int ans = 1e9;
    for (auto p : a) {
        ans = min(ans, p);
    }
    return ans;
}

void Solve() {
    int n, k; cin >> n >> k;

    vector<vector<int>> M(n);
    for (int i = 0; i < n; i++) {
        M[i].resize(n);
    }

    int x = 0;
    int y = 0;

    while (k > 0) {
        for (int i = 0; i < n; i++) {
            M[(x + i) % n][y + i] = 1;
            --k;
            if (k == 0) {
                break;
            }
        }
        x += 1;
        x %= n;
    }

    vector<int> S;
    vector<int> C;

    for (int i = 0; i < n; i++) {
        int now = 0;
        for (int j = 0; j < n; j++) {
            now += M[i][j];
        }
        S.push_back(now);
    }

    for (int i = 0; i < n; i++) {
        int now = 0;
        for (int j = 0; j < n; j++) {
            now += M[j][i];
        }
        C.push_back(now);
    }

    cout << (Max(S) - Min(S)) * (Max(S) - Min(S)) + (Max(C) - Min(C)) * (Max(C) - Min(C)) << '\n';

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << M[i][j];
        } cout << '\n';
    }
}

int main() {
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
