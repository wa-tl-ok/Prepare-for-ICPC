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
#include <iomanip>

using namespace std;

#define int long long

int bs_ll(vector<int>& arr, int target) {
    if (arr[0] >= target) {
        return -1;
    }
    int left = 0;
    int right = arr.size() - 1;
    while (left < right) {
        int mid = (left + right) / 2;
        if (arr[mid] >= target) {
            right = mid - 1;
        }
        else {
            if (arr[mid + 1] >= target) {
                return mid;
            }
            left = mid + 1;
        }
    }
    return left;
}

int bs_rr(vector<int>& arr, int target) {
    if (arr[arr.size() - 1] <= target) {
        return -1;
    }
    int left = 0;
    int right = arr.size() - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (arr[mid] <= target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return left;
}

int Find_L(int L, vector<int>& a) {
    int p = bs_ll(a, L);
    if (p == -1) {
        return 0;
    }
    else {
        return p + 1;
    }
}

int Find_R(int R, vector<int>& a) {
    int p = bs_rr(a, R);
    if (p == -1) {
        return 0;
    }
    else {
        return a.size() - p;
    }
}

void Solve() {
    int n; cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    map<int, vector<int>> id;
    for (int i = 0; i < n; i++) {
        id[a[i]].push_back(i);
    }

    int ans = 0;
    for (int l = 1; l < n - 2; l++) {
        for (int r = l + 1; r < n - 1; r++) {
            int F = a[l];
            int S = a[r];

            int FF = Find_L(l, id[S]);
            int SS = Find_R(r, id[F]);

            ans += FF * SS;
        }
    }

    cout << ans << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int multitest = true;
    if (multitest == true) {
        int ctt; cin >> ctt;

        for (int i = 0; i < ctt; i++) {
            Solve();
        }
    }
    else {
        Solve();
    }

    return 0;
}
