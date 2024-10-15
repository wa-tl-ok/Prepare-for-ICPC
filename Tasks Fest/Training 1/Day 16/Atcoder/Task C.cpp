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

vector<vector<int>> G; 
vector<bool> vis;
int K = 0;

bool dfs(int u) {
    vis[u] = true;
    bool cur = false;
    for (auto v : G[u]) {
        if (vis[v] == false) {
            bool ans = dfs(v);
            if (ans == false) {
                cur = true;
            }
        }
    }
    vis[u] = false;
    ++K;
    return cur;
}

void Solve() {
    int n, q; cin >> n >> q;
    map<int, set<int>> F;
    for (int i = 0; i < q; i++) {
        int t; cin >> t;
        if (t == 1) {
            int a, b; cin >> a >> b;
            F[a].insert(b);
        }
        else if (t == 2) {
            int a, b; cin >> a >> b;
            F[a].erase(b);
        }
        else {
            int a, b; cin >> a >> b;
            if (F[a].find(b) != F[a].end() && F[b].find(a) != F[b].end()) {
                cout << "Yes\n";
            }
            else {
                cout << "No\n";
            }
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
