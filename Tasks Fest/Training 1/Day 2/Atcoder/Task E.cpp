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
    int n, k, m;
    cin >> n >> m >> k;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<vector<Int>> C(2001, vector<Int>(2001));
    for (int i = 0; i < 2001; i++) {
        for (int j = 0; j <= i; j++) {
            if (j == 0 || i == j) {
                C[i][j] = 1;
            }
            else {
                C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
            }
        }
    }

    Int ans = 0;

    for (int cur = 1; cur <= m; cur++) {
        int bigger = 0;
        int zeroes = 0;

        for (int i = 0; i < n; i++) {
            if (a[i] >= cur) {
                ++bigger;
            }
            if (a[i] == 0) {
                ++zeroes;
            }
        }

        int need = n - k + 1 - bigger;

        if (need <= 0) {
            ans += Int(1);
            continue;
        }

        if (need > zeroes) {
            ans += Int(0);
            continue;
        }

        Int p = Int(m - cur + 1) / Int(m);

        for (int j = need; j <= zeroes; j++) {
            ans += C[zeroes][j] * p.pow(j) * (Int(1) - p).pow(zeroes - j);
        }
    }

    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int multitest = false;
    if (multitest == true) {
        int ctt;
        cin >> ctt;

        for (int i = 0; i < ctt; i++) {
            Solve();
        }
    }
    else {
        Solve();
    }

    return 0;
}
