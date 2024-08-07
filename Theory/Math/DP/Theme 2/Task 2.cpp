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

long long a[45][2][2];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n; cin >> n;

    if (n == 1) {
        cout << 2;
        return 0;
    }

    a[2][0][0] = 1;
    a[2][0][1] = 1;
    a[2][1][0] = 1;
    a[2][1][1] = 1;

    for (int i = 3; i <= 40; i++) {
        a[i][0][0] = a[i - 1][1][0] + a[i - 1][0][0];
        a[i][0][1] = a[i - 1][1][0] + a[i - 1][0][0];
        a[i][1][0] = a[i - 1][0][1] + a[i - 1][1][1];
        a[i][1][1] = a[i - 1][0][1];
    }

    cout << a[n][0][0] + a[n][0][1] + a[n][1][0] + a[n][1][1];

    return 0;
}
