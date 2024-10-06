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

long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }

    return a;
}

long long lcm(long long a, long long b) {
    if ((double)(a) * (b / gcd(a, b)) > 2e18) {
        return (long long)2e18;
    }
    else {
        return (a) * (b / gcd(a, b));
    }
}

void Solve() {
    int n; cin >> n;
    vector<int> a(n + 2, 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<int> c;
    for (int i = 0; i < a.size() - 1; i++) {
        int f = a[i];
        int s = a[i + 1];
        c.push_back(lcm(f, s));
    }

    string ans = "YES";
    for (int i = 0; i < c.size() - 1; i++) {
        if (gcd(c[i], c[i + 1]) != a[i + 1]) {
            ans = "NO";
        }
    }

    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int multitest = true;
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
