#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>
#include <deque>
#include <array>
#include <list>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <string>
#include <cstring>
#include <random>
#include <bitset>
#include <cassert>

using namespace std;

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

int bs_lr(vector<int>& arr, int target) {
    if (arr[arr.size() - 1] < target) {
        return -1;
    }
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

int bs_rl(vector<int>& arr, int target) {
    if (arr[0] > target) {
        return -1;
    }
    int left = 0;
    int right = arr.size() - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (arr[mid] > target) {
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }
    return right;
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

void run_tests() {
    vector<int> arr = { 1, 2, 4, 4, 5, 6, 8, 10 };

    // Test bs_ll
    assert(bs_ll(arr, 5) == 3);
    assert(bs_ll(arr, 1) == -1);
    assert(bs_ll(arr, 8) == 5);

    // Test bs_lr
    assert(bs_lr(arr, 4) == 2);
    assert(bs_lr(arr, 7) == 6);
    assert(bs_lr(arr, 10) == 7);
    assert(bs_lr(arr, 11) == -1);

    // Test bs_rl
    assert(bs_rl(arr, 4) == 3);
    assert(bs_rl(arr, 6) == 5);
    assert(bs_rl(arr, 0) == -1);

    // Test bs_rr
    assert(bs_rr(arr, 5) == 5);
    assert(bs_rr(arr, 4) == 4);
    assert(bs_rr(arr, 10) == -1);
    assert(bs_rr(arr, 0) == 0);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    run_tests();

    return 0;
}
