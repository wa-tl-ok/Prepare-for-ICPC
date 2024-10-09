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
    vector<int> vec(n);
    for (int i = 0; i < n; i++) {
        cin >> vec[i];
    }

    map<int, int> C;
    for (int i = 0; i < n; i++) {
        if (C[vec[i]] >= 1) {
            C[vec[i]] += 1;
        }
        else {
            C[vec[i]] = 1;
        }
    }

    int elem1 = -1;
    int elem2 = -1;
    for (auto P : C) {
        if (P.second >= 2) {
            if (elem1 == -1) {
                elem1 = P.first;
            }
            else if (elem2 == -1) {
                elem2 = P.first;
            }
        }
    }

    if (elem2 == -1) {
        cout << -1 << '\n';
        return;
    }

    vector<int> ans(n, 1);

    bool was1 = false;
    bool was2 = false;

    for (int i = 0; i < n; i++) {
        if (vec[i] == elem1 && was1 == false) {
            ans[i] = 2;
            was1 = true;
        }
        if (vec[i] == elem2 && was2 == false) {
            ans[i] = 3;
            was2 = true;
        }
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i] << ' ';
    } cout << '\n';
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
