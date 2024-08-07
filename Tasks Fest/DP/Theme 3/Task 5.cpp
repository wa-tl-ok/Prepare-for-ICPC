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

int a[55][55];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, m; cin >> n >> m;

    for (int i = 0; i < 55; i++) {
        for (int j = 0; j < 55; j++) {
            a[i][j] = 0;
        }
    }
    a[1][1] = 1;

    for (int i = 2; i <= n; i++) {
        for (int j = 2; j <= m; j++) {
            a[i][j] = a[i - 2][j - 1] + a[i - 1][j - 2];
        }
    }

    cout << a[n][m];

    return 0;
}
