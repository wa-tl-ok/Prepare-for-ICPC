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

void Solve() {
    int n; cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int ans = 0;

    int pos = 0;
    int neg = 0;

    int k = 0;

    multiset<int> OUT;

    for (int i = 0; i < n; i++) {
        if (a[i] >= 0) {
            pos += a[i];
            ++k;
        }
        else {
            neg += abs(a[i]);
            ++k;

            OUT.insert(abs(a[i]));
        }

        if (pos < neg) {
            while (neg > pos) {
                auto it = OUT.end();
                --it;

                neg -= *it;
                OUT.erase(it);

                --k;
            }
        }
        
        ans = max(ans, k);
    }

    cout << ans;
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
