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

int Go(vector<vector<char>>& a, int x, int y, int r) {
    int f = 1;
    for (int i = 1; i <= r; i++) {
        if (a[x + i][y + i] != '#') {
            return 0;
        }
        if (a[x - i][y + i] != '#') {
            return 0;
        }
        if (a[x + i][y - i] != '#') {
            return 0;
        }
        if (a[x - i][y - i] != '#') {
            return 0;
        }
    }
    return f;
}

int Find(int s, vector<vector<char>>& a) {
    int n = a.size();
    int m = a[0].size();
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int r = (s - 1) / 2;
            if (i - r >= 0 && i + r < n && j - r >= 0 && j + r < m) {
                if (Go(a, i, j, r) == 1 && a[i][j] == '#') {
                    ++ans;

                    int x = i;
                    int y = j;

                    for (int u = 1; u <= r; u++) {
                        a[x + u][y + u] = '.';
                        a[x - u][y + u] = '.';
                        a[x + u][y - u] = '.';
                        a[x - u][y - u] = '.';
                    }

                    a[x][y] = '.';
                }
            }
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, m; cin >> n >> m;
    vector<vector<char>> a(n);
    for (int i = 0; i < n; i++) {
        a[i].resize(m);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }
    vector<int> ANS;
    for (int i = min(n, m); i >= 0; i--) {
        ANS.push_back(Find((i + 1) * 2 + 1, a));
    }

    reverse(ANS.begin(), ANS.end());

    for (int i = 0; i < ANS.size() - 1; i++) {
        cout << ANS[i] << ' ';
    }

    return 0;
}
