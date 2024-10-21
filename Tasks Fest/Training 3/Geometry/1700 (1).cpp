//https://codeforces.com/contest/630/problem/Q

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

long double S3(int a) {
    return a * a * a / sqrt(2) / 6;
}

long double S4(int a) {
    return a * a * a / sqrt(2) / 3;
}

long double S5(int a) {
    return a * a * a * 0.3015028323;
}

void Solve() {
    int l3, l4, l5; cin >> l3 >> l4 >> l5;
    cout << fixed << setprecision(9) << S3(l3) + S4(l4) + S5(l5);
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
