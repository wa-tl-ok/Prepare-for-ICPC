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

long long modInverse(long long a, long long mod) {
    long long m0 = mod, y = 0, x = 1;

    if (mod == 1) {
        return 0;
    }

    while (a > 1) {
        long long q = a / mod;
        long long t = mod;

        mod = a % mod, a = t;
        t = y;

        y = x - q * y;
        x = t;
    }

    if (x < 0) {
        x += m0;
    }

    return x;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    long long n; cin >> n;
    long long m; cin >> m;

    long long t = modInverse(n, m);
    cout << t;

    return 0;
}
