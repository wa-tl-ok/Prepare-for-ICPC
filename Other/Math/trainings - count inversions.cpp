//https://codeforces.com/gym/100246

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

vector <long long> a;

long long nearestPowerOfTwo(long long n) {
    if (n == 0) {
        return 1;
    }
    long long power = 0;
    while (pow(2, power) <= n) {
        power++;
    }
    return pow(2, power);
}

long long mergeinverse(vector <long long>& a) {
    long long inv_count = 0;
    if (a.size() > 1) {
        long long mid = a.size() / 2;

        vector<long long> left(a.begin(), a.begin() + mid);
        vector<long long> right(a.begin() + mid, a.end());

        inv_count += mergeinverse(left);
        inv_count += mergeinverse(right);

        long long i = 0, j = 0, k = 0;

        while (i < left.size() && j < right.size()) {
            if (left[i] <= right[j]) {
                a[k] = left[i];
                i++;
            }
            else {
                a[k] = right[j];
                j++;
                inv_count += (long long)left.size() - i;
            }
            k++;
        }
        while (i < left.size()) {
            a[k] = left[i];
            i++;
            k++;
        }
        while (j < right.size()) {
            a[k] = right[j];
            j++;
            k++;
        }
    }
    return inv_count;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    freopen("inverse.in", "r", stdin);
    freopen("inverse.out", "w", stdout);

    long long n; 
    long long q; 
    long long p; 
    cin >> n;

    long long s = nearestPowerOfTwo(n);
    a.resize(s);

    for (long long i = 0; i < s; i++) {
        a[i] = 1e18;
    }

    for (long long i = 0; i < n; i++) {
        cin >> a[i];
    }

    cout << mergeinverse(a);

    return 0;
}
