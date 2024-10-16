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

    vector<int> a;
    for (int i = 0; i < n * 2; i++) {
        int t; cin >> t;
        a.push_back(t);
    }
    sort(a.begin(), a.end());

    vector<int> st;
    int mx = -1;
    for (auto p : a) {
        mx = max(mx, p);
    }
    for (auto p : a) {
        st.push_back(mx + p);
    }
    st.pop_back();

    for (auto s : st) {
        multiset<int> b;
        for (auto p : a) {
            b.insert(p);
        }

        vector<pair<int, int>> ans;

        int now = s;
        while (b.size() > 0) {
            auto it = b.end();
            --it;
            
            int mx = *it;
            b.erase(it);

            auto itt = b.find(now - mx);
            if (itt == b.end()) {
                break;
            }

            b.erase(itt);
            ans.push_back({ now - mx, mx });
            now = mx;
        }

        if (b.size() == 0) {
            cout << "YES\n";
            cout << s << '\n';
            for (auto p : ans) {
                cout << p.first << ' ' << p.second << '\n';
            }
            return;
        }
    }

    cout << "NO\n";
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
