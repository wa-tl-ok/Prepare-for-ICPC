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

    vector<int> a(50);
    a[1] = 1;
    a[2] = 2;
    a[3] = 4;

    for (int i = 4; i < 50; i++) {
        a[i] = a[i - 1] + a[i - 2] + a[i - 3];
    }

    cout << a[n];

    return 0;
}
