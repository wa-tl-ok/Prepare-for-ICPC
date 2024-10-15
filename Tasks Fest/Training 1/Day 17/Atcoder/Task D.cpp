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
    int F0 = 0, F1 = 0; 
    int n; cin >> n;
    int m; cin >> m;
    map<int, int> M;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        M[x] += x;
        if (x == 0) {
            F0 = 1;
        }
        if (x == m - 1) {
            F1 = 1;
        }
    }
    if (F0 + F1 != 2) {
        int last = -1;
        int now = 0;
        multiset<int> GO;

        for (auto p : M) {
            int f = p.first;
            int s = p.second;
            if (abs(last - f) <= 1) {
                now += s;
            }
            else {
                if (last != -1) {
                    GO.insert(now);
                }
                now = s;
            }
            last = f;
        }
        GO.insert(now);

        int SUM = 0;
        int mx = 0;
        for (auto a : GO) {
            SUM += a;
            mx = max(mx, a);
        }

        cout << SUM - mx;
    }
    else {
        int last = -1;
        int now = 0;
        multiset<int> GO;

        for (auto p : M) {
            int f = p.first;
            int s = p.second;
            if (abs(last - f) <= 1) {
                now += s;
            }
            else {
                if (last != -1) {
                    GO.insert(now);
                }
                now = s;
            }
            last = f;
        }
        
        if (GO.size() == 0) {
            cout << 0;
        }
        else {
            int p = *GO.begin();
            p += now;
            GO.erase(*GO.begin());
            GO.insert(p);\

            int SUM = 0;
            int mx = 0;
            for (auto a : GO) {
                SUM += a;
                mx = max(mx, a);
            }

            cout << SUM - mx;
        }
    }
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
