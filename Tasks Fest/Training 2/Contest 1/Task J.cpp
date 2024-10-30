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

struct Int {
    int value;
    static const int mod = 1e9 + 7;

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

vector<Int> Fact;

Int Find(pair<int, int> f, pair<int, int> s) {
    int n = s.first - f.first + s.second - f.second;
    int k = s.first - f.first;
    return Fact[n] / (Fact[k] * Fact[n - k]);
}

void Solve() {
    int h, w, n;
    cin >> h >> w >> n;

    map<int, vector<int>> m;
    vector<pair<int, int>> ALL;
    set<int> ALL_X;

    for (int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        m[x].push_back(y);
        ALL.push_back({ x, y });
        ALL_X.insert(x);
    }

    m[h].push_back(w);
    ALL.push_back({ h, w });
    ALL_X.insert(h);

    for (auto x : ALL_X) {
        sort(m[x].begin(), m[x].end());
    }

    map<pair<int, int>, Int> var;
    var[{1, 1}] = Int(1);
    for (auto x : ALL_X) {
        for (auto y : m[x]) {
            pair<int, int> now = { x, y };
            var[now] = Find({ 1, 1 }, now);
            for (auto last : ALL) {
                if (last.first <= now.first && last.second <= now.second && last != now) {
                    var[now] -= var[last] * Find(last, now);
                }
            }
        }
    }
    cout << var[{h, w}];
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    Fact.resize(2e5 + 5);
    Fact[0] = 1;
    for (int i = 1; i < Fact.size(); i++) {
        Fact[i] = Fact[i - 1] * Int(i);
    }

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
