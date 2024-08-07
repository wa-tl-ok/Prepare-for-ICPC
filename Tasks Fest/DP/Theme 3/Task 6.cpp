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

int n, m;

int GO(int i, int j) {
    if (i == 1 && j == 1) {
        return 1;
    }

    int S = 0;

    if (i - 2 >= 1 && j - 1 >= 1) {
        S += GO(i - 2, j - 1);
    }
    if (i - 2 >= 1 && j + 1 <= m) {
        S += GO(i - 2, j + 1);
    }
    if (i + 1 <= n && j - 2 >= 1) {
        S += GO(i + 1, j - 2);
    }
    if (i - 1 >= 1 && j - 2 >= 1) {
        S += GO(i - 1, j - 2);
    }

    return S;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    cout << GO(n, m);

    return 0;
}
