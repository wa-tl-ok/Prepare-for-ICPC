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

    if (n == 0) {
        cout << 0 << endl;
        return 0;
    }

    vector<int> l;
    vector<int> ind(n);
    vector<int> pr(n, -1);

    for (int i = 0; i < n; ++i) {
        int p = bs_lr(l, a[i]);

        if (p == l.size()) {
            l.push_back(a[i]);
            ind[p] = i;
        }
        else {
            l[p] = a[i];
            ind[p] = i;
        }

        if (p > 0) {
            pr[i] = ind[p - 1];
        }
    }

    vector<int> lis(l.size());
    int c = ind[l.size() - 1];

    for (int i = l.size() - 1; i >= 0; --i) {
        lis[i] = a[c];
        c = pr[c];
    }

    for (int i = 0; i < l.size(); ++i) {
        cout << lis[i] << " ";
    }

    return 0;
}
