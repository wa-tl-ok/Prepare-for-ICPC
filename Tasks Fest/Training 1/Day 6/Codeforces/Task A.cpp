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

void Solve() {
    int n; cin >> n;

    int z1 = 0;
    int e1 = 0;

    vector<int> A;

    for (int i = 0; i < n; i++) {
        int t; cin >> t;
        if (t == 0) {
            z1 += 1;
            A.push_back(0);
        }
        else {
            e1 += 1;
            A.push_back(1);
        }
    }

    int z2 = 0;
    int e2 = 0;

    vector<int> B;

    for (int i = 0; i < n; i++) {
        int t; cin >> t;
        if (t == 0) {
            z2 += 1;
            B.push_back(0);
        }
        else {
            e2 += 1;
            B.push_back(1);
        }
    }

    int k = 0;

    for (int i = 0; i < n; i++) {
        if (A[i] != B[i]) {
            ++k;
        }
    }

    cout << min(n - min(z1, z2) - min(e1, e2) + 1, k) << '\n';
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
