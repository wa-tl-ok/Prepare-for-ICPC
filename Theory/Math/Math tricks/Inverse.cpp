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
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    vector<long long> a = { 5, 4, 3, 2, 1 };
    cout << mergeinverse(a);

    return 0;
}
