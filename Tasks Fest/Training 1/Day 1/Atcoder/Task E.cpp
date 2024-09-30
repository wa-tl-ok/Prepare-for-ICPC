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

int n;
map<int, int> P;
map<int, bool> C;

int go(int x) {
    if (x > n) {
        return 0;
    }
    else if (x == n) {
        return 1;
    }
    else {
        int s = 0;

        for (int i = 2; i <= 6; i++) {
            if (C[x * i] == true) {
                s += P[x * i];
            }
            else {
                s += go(x * i);
            }
        }

        s *= 598946612;
        s %= 998244353;

        P[x] = s;
        C[x] = true;

        return s;
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;

    P[n] = 1;
    C[n] = true;

    cout << go(1);

    return 0;
}
