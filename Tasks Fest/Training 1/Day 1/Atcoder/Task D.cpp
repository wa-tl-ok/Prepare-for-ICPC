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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n; cin >> n;
    vector<int> A;

    vector<int> c(1000005);
    for (int i = 0; i < 1000005; i++) {
        c[i] = 1;
    }

    for (int i = 2; i < 1000005; i++) {
        if (c[i] == 1) {
            int j = i;

            while (j + i < 1000005) {
                j += i;
                c[j] = 0;
            }

            A.push_back(i);
        }
    }

    int ans = 0;

    for (int i = 0; i < A.size() - 2; i++) {
        if (A[i] > n) {
            break;
        }

        if (A[i] * A[i] > n) {
            break;
        }

        for (int j = i + 1; j < A.size() - 1; j++) {
            if (A[i] * A[i] * A[j] > n) {
                break;
            }

            for (int k = j + 1; k < A.size(); k++) {
                if (A[i] * A[i] * A[j] * A[k] > n) {
                    break;
                }

                if (A[i] * A[i] * A[j] * A[k] * A[k] > n) {
                    break;
                }

                ++ans;
            }
        }
    }

    cout << ans;

    return 0;
}
