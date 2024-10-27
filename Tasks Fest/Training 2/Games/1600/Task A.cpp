//https://codeforces.com/contest/346/problem/A

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

void Solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int mx = -1e18;
    for (int i = 0; i < n; i++) {
        mx = max(mx, a[i]);
    }
    int g = gcd_array(a);
    if (abs((mx - g) / g - n) % 2 == 0) {
        cout << "Alice";
    }
    else {
        cout << "Bob";
    }
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
