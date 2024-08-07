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

int a[15][15];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, m; cin >> n >> m;

    a[1][1] = 1;
    for (int i = 1; i <= n; i++) {
        a[i][1] = 1;
    }
    for (int i = 1; i <= m; i++) {
        a[1][i] = 1;
    }

    for (int i = 2; i <= n; i++) {
        for (int j = 2; j <= m; j++) {
            a[i][j] = a[i - 1][j] + a[i][j - 1];
        }
    }

    cout << a[n][m];

    return 0;
}
