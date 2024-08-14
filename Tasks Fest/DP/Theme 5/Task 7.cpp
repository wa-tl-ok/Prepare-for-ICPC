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

int bs_lr(vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (arr[mid] < target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return left;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, a1, k, b, m;
    cin >> n >> a1 >> k >> b >> m;

    vector<int> a(n);
    a[0] = a1;
    for (int i = 1; i < n; i++) {
        a[i] = (k * a[i - 1] + b) % m;
    }

    vector<int> l;
    for (int i = 0; i < n; ++i) {
        int p = bs_lr(l, a[i]);

        if (p == l.size()) {
            l.push_back(a[i]);
        }
        else {
            l[p] = a[i];
        }
    }

    cout << l.size();

    return 0;
}
