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

void Add(vector<int>& S, int e, int n) {
    vector<int> go;
    for (auto g : S) {
        while (g * e <= n) {
            g *= e;
            go.push_back(g);
        }
    }
    for (auto g : go) {
        S.push_back(g);
    }
}

bool check(int x) {
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) return false;
    }
    return true;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, p; cin >> n >> p;

    vector<int> s;
    for (int i = 2; i <= p; i++) {
        if (check(i) == true) {
            s.push_back(i);
        }
    }

    vector<int> U = { 1 };
    vector<int> V = { 1 };

    for (auto e : s) {
        if (U.size() > V.size()) {
            Add(V, e, n);
        }
        else {
            Add(U, e, n);
        }
    }

    sort(U.begin(), U.end());
    sort(V.begin(), V.end());

    int ans = 0;

    int j = (int)V.size() - 1;
    for (int i = 0; i < U.size(); i++) {
        while (U[i] * V[j] > n) {
            j--;

            if (j < 0) {
                break;
            }
        }
        if (j >= 0) {
            if (U[i] * V[j] <= n) {
                ans += j + 1;
            }
        }
        else {
            break;
        }
    }

    cout << ans;

    return 0;
}
