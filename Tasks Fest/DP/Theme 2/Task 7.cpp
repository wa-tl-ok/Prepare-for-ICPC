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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n; cin >> n;

    vector<int> a(n + 1);
    a[1] = 0;

    vector<int> p(n + 1);
    p[1] = -1;

    for (int i = 2; i <= n; i++) {
        a[i] = a[i - 1];
        p[i] = 1;

        if (i % 2 == 0) {
            if (a[i / 2] < a[i]) {
                a[i] = a[i / 2];
                p[i] = 2;
            }
        }

        if (i % 3 == 0) {
            if (a[i / 3] < a[i]) {
                a[i] = a[i / 3];
                p[i] = 3;
            }
        }

        a[i] += 1;
    }

    vector<int> ans;

    while (n != 1) {
        ans.push_back(p[n]);

        if (p[n] == 1) {
            n -= 1;
        }
        else if (p[n] == 2) {
            n /= 2;
        }
        else {
            n /= 3;
        }
    }

    reverse(ans.begin(), ans.end());

    for (int i = 0; i < (int)ans.size(); i++) {
        cout << ans[i];
    }

    return 0;
}
