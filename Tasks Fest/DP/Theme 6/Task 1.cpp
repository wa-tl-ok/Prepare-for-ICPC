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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n; cin >> n;

    if (n == 0) {
        cout << 0;
        return 0;
    }

    vector<int> a(n + 1);
    a[1] = 1;

    for (int i = 2; i <= n; i++) {
        int mn = 1e9;

        for (int j = 1; j <= 100; j++) {
            if (i - j * j * j >= 0) {
                mn = min(mn, a[i - j * j * j]);
            }
        }

        a[i] = mn + 1;
    }

    cout << a[a.size() - 1];

    return 0;
}
