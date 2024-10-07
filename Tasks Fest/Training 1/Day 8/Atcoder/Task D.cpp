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

map<int, bool> V;
map<int, int> Z;

int f(int n) {
    if (n == 0) {
        return 1;
    }

    int v = true;
    int z = 0;

    if (V[n / 2] == true && V[n / 3] == true) {
        z = Z[n / 2] + Z[n / 3];
    }

    if (V[n / 2] == true && V[n / 3] == false) {
        z = Z[n / 2] + f(n / 3);
    }

    if (V[n / 2] == false && V[n / 3] == true) {
        z = f(n / 2) + Z[n / 3];
    }

    if (V[n / 2] == false && V[n / 3] == false) {
        z = f(n / 2) + f(n / 3);
    }

    V[n] = v;
    Z[n] = z;

    return z;
}

void Solve() {
    int n; cin >> n;
    cout << f(n);
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
