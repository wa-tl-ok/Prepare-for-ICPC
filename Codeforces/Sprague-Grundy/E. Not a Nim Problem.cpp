//https://codeforces.com/contest/2004/problem/E

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

    const int mx = 10000005;

    vector<bool> vis(mx, true);
    for (int i = 2; i * i < mx; ++i) {
        if (vis[i] == true) {
            for (int j = i * i; j < mx; j += i) {
                vis[j] = false;
            }
        }
    }

    vector<int> primes;
    for (int i = 2; i < mx; ++i) {
        if (vis[i] == true) {
            primes.push_back(i);
        }
    }

    vector<int> minp(mx, 0);
    minp[1] = 1;
    for (auto p : primes) {
        minp[p] = p;
    }
    for (int x = 2; x < mx; x++) {
        for (auto p : primes) {
            if (x * p > mx) {
                break;
            }
            minp[x * p] = p;
            if (p == minp[x]) {
                break;
            }
        }
    }

    vector<int> sg(mx, 0);
    sg[1] = 1;
    for (int i = 1; i < primes.size(); i++) {
        sg[primes[i]] = i + 1;
    }
    for (int i = 1; i < mx; i++) {
        sg[i] = sg[minp[i]];
    }

    int t; cin >> t;
    for (int i = 0; i < t; i++) {
        int n; cin >> n;
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int a; cin >> a;
            ans ^= sg[a];
        }
        if (ans != 0) {
            cout << "Alice\n";
        }
        else {
            cout << "Bob\n";
        }
    }

    return 0;
}
