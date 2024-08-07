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

    vector<int> c(n);
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }

    if (n == 0) {
        cout << 0;
        return 0;
    }

    if (n == 1) {
        cout << c[0];
        return 0;
    }

    vector<int> a(n);
    a[0] = c[0];
    a[1] = c[1];

    for (int i = 2; i < n; i++) {
        a[i] = min(a[i - 1], a[i - 2]) + c[i];
    }

    cout << a[n - 1];

    return 0;
}
