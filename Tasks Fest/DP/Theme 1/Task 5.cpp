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

    vector<int> a(1005);
    a[0] = 1;
    a[1] = 1;

    for (int i = 2; i < 1005; i++) {
        if (i % 2 == 0) {
            a[i] = a[i / 2] + 1;
        }
        else {
            a[i] = a[(i + 1) / 2] + 1 + a[(i - 1) / 2];
        }
    }

    cout << a[n];

    return 0;
}

/*

a[2n] = a[n] + 1
a[2n + 2] = a[2n + 1] - a[n] => a[2n + 1] = a[2n + 2] + a[n] = a[2(n + 1)] + a[n] = a[n + 1] + 1 + a[n]

a[2n] = a[n] + 1
a[2n + 1] = a[n + 1] + 1 + a[n]

*/
