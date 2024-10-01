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

long long Fast_power_mod(long long a, long long n, long long mod) {
    if (n == 0) {
        return 1;
    }

    long long result = 1;
    long long base = a;

    while (n > 0) {
        if (n % 2 == 1) {
            result = (result * base) % mod;
        }

        base = (base * base) % mod;
        n = n / 2;
    }

    return result % mod;
}

long long Fast_power(long long a, long long n) {
    if (n == 0) {
        return 1;
    }

    long long result = 1;
    long long base = a;

    while (n > 0) {
        if (n % 2 == 1) {
            result = result * base;
        }

        base = base * base;
        n = n / 2;
    }

    return result;
}

long long safe_pow(long long a, long long b) {
    long long p = 1;

    for (long long i = 0; i < b; i++) {
        double q = p;
        q *= a;

        if (q > 2e18) {
            return 2e18;
        }

        p *= a;
    }

    return p;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    long long base = 2;
    long long exponent = 10;
    long long mod = 1000;

    long long result_mod = Fast_power_mod(base, exponent, mod);
    cout << "Fast_power_mod(" << base << ", " << exponent << ", " << mod << ") = " << result_mod << "\n";

    long long result = Fast_power(base, exponent);
    cout << "Fast_power(" << base << ", " << exponent << ") = " << result << "\n";

    return 0;
}
