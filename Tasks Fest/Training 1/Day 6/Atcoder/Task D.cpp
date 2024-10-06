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
    return sqrt((A.first - B.first) * (A.first - B.first) + (A.second - B.second) * (A.second - B.second));
}

double GO(vector<pair<pair<int, int>, pair<int, int>>> V, int mask, int s, int t) {
    for (int i = 0; i < V.size(); i++) {
        if (((mask >> i) & 1) == 1) {
            swap(V[i].first, V[i].second);
        }
    } 

    double ans = 0;
    pair<int, int> NOW = { 0, 0 };
    for (int i = 0; i < V.size(); i++) {
        ans += dist(NOW, V[i].first) / s;
        ans += dist(V[i].first, V[i].second) / t;
        NOW = V[i].second;
    }

    return ans;
}

void Solve() {
    int n, s, t; 
    cin >> n >> s >> t;

    vector<pair<pair<int, int>, pair<int, int>>> V;
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2; 
        cin >> x1 >> y1 >> x2 >> y2;
        V.push_back({{x1, y1}, {x2, y2}});
    }

    double ans = 1e18;

    vector<int> p;
    for (int i = 0; i < n; i++) {
        p.push_back(i);
    }

    do {
        vector<pair<pair<int, int>, pair<int, int>>> VV;
        for (int i = 0; i < n; i++) {
            VV.push_back(V[p[i]]);
        }
        for (int i = 0; i < pow(2, n); i++) {
            ans = min(ans, GO(VV, i, s, t));
        }
    } while (next_permutation(p.begin(), p.end()));

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
