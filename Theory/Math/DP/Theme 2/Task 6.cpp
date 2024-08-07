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

    vector<int> a(n + 1);
    a[1] = 0;

    for (int i = 2; i <= n; i++) {
        a[i] = a[i - 1];
        
        if (i % 2 == 0) {
            a[i] = min(a[i], a[i / 2]);
        }

        if (i % 3 == 0) {
            a[i] = min(a[i], a[i / 3]);
        }

        a[i] += 1;
    }

    cout << a[n];

    return 0;
}
