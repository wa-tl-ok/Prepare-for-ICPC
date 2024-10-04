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

#define int long long

struct Int {
    int value;
    static const int mod = 998244353;

    Int() : value(0) {}

    Int(int value) : value(value% mod) {}

    Int(const Int& other) : value(other.value) {}

    Int operator+(const Int& other) const {
        return Int((value + other.value) % mod);
    }

    Int operator-(const Int& other) const {
        return Int((value - other.value + mod) % mod);
    }

    Int operator*(const Int& other) const {
        return Int((1LL * value * other.value) % mod);
    }

    Int operator/(const Int& other) const {
        return *this * Int(modInverse(other.value, mod));
    }

    Int pow(int exp) const {
        if (exp == 0) return Int(1);
        Int half = pow(exp / 2);
        if (exp % 2 == 0) return half * half;
        else return half * half * *this;
    }

    Int& operator=(int newValue) {
        value = newValue % mod;
        return *this;
    }

    Int& operator+=(const Int& other) {
        return *this = *this + other;
    }

    Int& operator-=(const Int& other) {
        return *this = *this - other;
    }

    Int& operator*=(const Int& other) {
        return *this = *this * other;
    }

    Int& operator/=(const Int& other) {
        return *this = *this / other;
    }

    int gcdExtended(int a, int b, int& x, int& y) const {
        if (a == 0) {
            x = 0; y = 1;
            return b;
        }
        int x1, y1;
        int gcd = gcdExtended(b % a, a, x1, y1);
        x = y1 - (b / a) * x1; y = x1;
        return gcd;
    }

    int modInverse(int a, int m) const {
        int x, y;
        int g = gcdExtended(a, m, x, y);
        return (x % m + m) % m;
    }

    friend std::ostream& operator<<(std::ostream& os, const Int& obj) {
        os << obj.value;
        return os;
    }
};

void Solve() {
    int n, p; cin >> n >> p;

    Int f = Int(p) / Int(100);
    Int s = Int(1) - f;

    vector<Int> dp(n + 1);
    dp[0] = Int(0);
    dp[1] = Int(1);

    for (int i = 2; i <= n; i++) {
        dp[i] = Int(1) + f * dp[i - 2] + s * dp[i - 1];
    }

    cout << dp[n];
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int multitest = false;
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
