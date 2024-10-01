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
    int n, x; cin >> n >> x;

    vector<int> p(n + 1); 
    int IND = 0;
    for (int i = 1; i <= n; i++) {
        cin >> p[i];

        if (p[i] == x) {
            IND = i;
        }
    }

    int l = 1;
    int r = n + 1;

    while (l + 1 != r) {
        int m = (l + r) / 2;

        if (p[m] <= x) {
            l = m;
        }
        else {
            r = m;
        }
    }

    if (p[l] == x) {
        cout << 0 << endl;
    }
    else {
        cout << 1 << endl;
        cout << IND << ' ' << l << endl;
    }
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
