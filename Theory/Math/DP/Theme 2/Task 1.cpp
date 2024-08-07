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

int a[105][2];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n; cin >> n;

    a[1][0] = 1;
    a[1][1] = 1;

    for (int i = 2; i < 105; i++) {
        a[i][0] = a[i - 1][0] + a[i - 1][1];
        a[i][1] = a[i - 1][1];
    }

    cout << a[n][0] + a[n][1];

    return 0;
}
