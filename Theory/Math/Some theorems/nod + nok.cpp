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

using namespace std;

long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }

    return a;
}

long long gcd_array(const vector<long long>& arr) {
    long long n = arr.size();
    if (n == 0) {
        return 0;
    }

    long long result = arr[0];
    for (long long i = 1; i < n; ++i) {
        result = gcd(result, arr[i]);
        if (result == 1) {
            break;
        }
    }

    return result;
}

long long lcm(long long a, long long b) {
    if ((double)(a) * (b / gcd(a, b)) > 2e18) {
        return (long long)2e18;
    }
    else {
        return (a) * (b / gcd(a, b));
    }
}

long long lcm_array(const vector<long long>& arr) {
    long long n = arr.size();
    if (n == 0) {
        return 0;
    }

    double result = arr[0];
    for (long long i = 1; i < n; ++i) {
        result = lcm((long long)result, arr[i]);
        if (result >= 2e18) {
            return (long long)2e18;
        }
    }

    return (long long)result;
}

#include <cassert>

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    vector<long long> test = { 12, 15, 20, 25, 30 };
    assert(gcd_array(test) == 1);
    assert(lcm_array(test) == 300);

    return 0;
}
