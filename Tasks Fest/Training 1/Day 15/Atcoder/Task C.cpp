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
    int n; cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    reverse(a.begin(), a.end());

    vector<int> ans;
    int k = 1;
    for (int i = 0; i < n - 1; i++) {
        if (a[i] != a[i + 1]) {
            ans.push_back(k);
            k = 1;
        }
        else {
            ++k;
        }
    }
    if (k > 0) {
        ans.push_back(k);
    }

    int l = ans.size();
    for (int i = 0; i < n - l; i++) {
        ans.push_back(0);
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i] << '\n';
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
