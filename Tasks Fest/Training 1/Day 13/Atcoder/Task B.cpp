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
#include <iomanip>

using namespace std;

#define int long long

double dist(pair<int, int> A, pair<int, int> B) {
    int x1 = A.first;
    int y1 = A.second;

    int x2 = B.first;
    int y2 = B.second;

    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

void Solve() {
    int n; cin >> n;
    
    vector<pair<int, int>> V;
    V.push_back({ 0, 0 });
    for (int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        V.push_back({ x, y });
    }
    V.push_back({ 0, 0 });

    double ans = 0;
    for (int i = 0; i < V.size() - 1; i++) {
        ans += dist(V[i], V[i + 1]);
    }

    cout << fixed << setprecision(6) << ans;
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
