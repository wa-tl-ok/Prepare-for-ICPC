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
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int now_min = 1;
    int now_max = n;

    int l = 0;
    int r = n - 1;

    while (l < r) {
        if (a[l] == now_min) {
            ++l;
            ++now_min;
        }
        else if (a[l] == now_max) {
            ++l;
            --now_max;
        }
        else if (a[r] == now_min) {
            --r;
            ++now_min;
        }
        else if (a[r] == now_max) {
            --r;
            --now_max;
        }
        else {
            cout << l + 1 << ' ' << r + 1 << '\n';
            return;
        }
    }

    cout << -1 << '\n';
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
