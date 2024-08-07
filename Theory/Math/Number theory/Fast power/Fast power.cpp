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

int Fast_power_mod(int a, int n, int mod) {
    if (n == 0) {
        return 1;
    }

    int result = 1;
    int base = a;

    while (n > 0) {
        if (n % 2 == 1) {
            result = (result * base) % mod;
        }

        base = (base * base) % mod;
        n = n / 2;
    }

    return result % mod;
}

int Fast_power(int a, int n) {
    if (n == 0) {
        return 1;
    }

    int result = 1;
    int base = a;

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

    int base = 2;
    int exponent = 10;
    int mod = 1000;

    int result_mod = Fast_power_mod(base, exponent, mod);
    cout << "Fast_power_mod(" << base << ", " << exponent << ", " << mod << ") = " << result_mod << "\n";

    int result = Fast_power(base, exponent);
    cout << "Fast_power(" << base << ", " << exponent << ") = " << result << "\n";

    return 0;
}
