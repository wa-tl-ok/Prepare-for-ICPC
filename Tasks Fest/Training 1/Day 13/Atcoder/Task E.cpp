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

int DP[1505][1505];

void Solve() {
    int n; cin >> n;

    for (int i = 0; i < 1505; i++) {
        for (int j = 0; j < 1505; j++) {
            DP[i][j] = 1e9;
        }
    }
    DP[0][0] = 0;

    int S = 0;

    vector<pair<int, int>> v;
    for (int i = 0; i < n; i++) {
        int t, p; cin >> t >> p;
        S += p;
        v.push_back({ t, p });
    }

    for (int i = 0; i < n; i++) {
        pair<int, int> P = v[i];

        int type = P.first;
        int weight = P.second;

        for (int j = 1504; j >= 0; j--) {
            for (int k = 1504; k >= 0; k--) {
                if (type != 3) {
                    ++DP[j][k];
                }

                if (j >= weight) {
                    if (type == 1) {
                        DP[j][k] = min(DP[j][k], DP[j - weight][k]);
                    }
                    else {
                        DP[j][k] = min(DP[j][k], DP[j - weight][k] + 1);
                    }
                }

                if (k >= weight) {
                    if (type == 2) {
                        DP[j][k] = min(DP[j][k], DP[j][k - weight]);
                    }
                    else {
                        DP[j][k] = min(DP[j][k], DP[j][k - weight] + 1);
                    }
                }
            }
        }
    }

    if (S % 3 != 0) {
        cout << -1;
    }
    else if (DP[S / 3][S / 3] >= 1e9) {
        cout << -1;
    }
    else {
        cout << DP[S / 3][S / 3];
    }
}

int main() {
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
