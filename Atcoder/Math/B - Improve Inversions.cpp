//https://atcoder.jp/contests/arc180/tasks/arc180_b

#include <iostream> 
#include <iomanip> 
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
#include <random> 

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, k; cin >> n >> k;
    vector<pair<int, int>> ans;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<pair<int, int>> P;
    for (int i = 0; i < n; i++) {
        P.push_back({ a[i], i });
    }

    sort(P.begin(), P.end());

    vector<int> q;
    for (int i = 0; i < n; i++) {
        q.push_back(P[i].second);
    }

    for (int i = 0; i < n; i++) {
        vector<int> r;
        for (int j = i; j >= 0; j--) {
            if (q[j] - q[i] >= k) {
                r.push_back(j);
            }
        }

        int s = i;
        for (auto t : r) {
            ans.push_back({ q[s], q[t] });
            swap(q[s], q[t]);
            s = t;
        }
    }

    cout << ans.size() << endl;
    for (auto p : ans) {
        cout << p.first + 1 << ' ' << p.second + 1 << endl;
    }

    return 0;
}
