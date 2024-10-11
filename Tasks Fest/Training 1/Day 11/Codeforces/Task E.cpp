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
    // INPUT BEGIN

    int n; cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        --a[i];
    }

    vector<int> b(n);
    for (int i = 0; i < n; i++) {
        cin >> b[i];
        --b[i];
    }

    // INPUT END

    // FORMING COLORS OF COMPONENTS BEGIN

    deque<int> S;
    for (int i = 1; i <= n; i++) {
        S.push_back(i);
    }

    vector<vector<int>> G;
    vector<int> vis;
    int c = 0;

    map<int, int> COLOR;

    function<void(int)> dfs = [&](int u) {
        vis[u] = c;
        COLOR[u] = c;
        for (auto v : G[u]) {
            if (vis[v] == -1) {
                dfs(v);
            }
        }
    };

    G.resize(n);
    for (int i = 0; i < n; i++) {
        G[a[i]].push_back(b[i]);
    }

    vis.resize(n);
    for (int i = 0; i < n; i++) {
        vis[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        if (vis[i] == -1) {
            dfs(i);
            ++c;
        }
    }

    map<int, int> sizec;
    map<int, vector<int>> elems;

    for (int i = 0; i < n; i++) {
        sizec[i] = 0;
        elems[i] = {};
    }
    for (int i = 0; i < n; i++) {
        sizec[vis[i]] += 1;
        elems[vis[i]].push_back(i);
    }

    // FORMING COLORS OF COMPONENTS END

    // GETTING ANS PROCESS BEGIN

    vector<int> bad;
    map<int, int> ans;
    bool F = true;

    function<void(int)> DFS = [&](int u) {
        vis[u] = 1;
        if (vis[G[u][0]] != -1 && sizec[COLOR[u]] % 2 == 1) {
            bad.push_back(u);
        }
        else {
            if (F == true) {
                ans[u] = S[0];
                S.pop_front();
                F = false;
            }
            else {
                ans[u] = S[S.size() - 1];
                S.pop_back();
                F = true;
            }
        }
        for (auto v : G[u]) {
            if (vis[v] == -1) {
                DFS(v);
            }
        }
    };

    for (int i = 0; i < n; i++) {
        vis[i] = -1;
    }

    for (int color = 0; color < n; color++) {
        if (sizec[color] == 1) {
            ans[elems[color][0]] = 0;
        }
        else if (sizec[color] > 1) {
            int head = elems[color][0];
            DFS(head);
        }
    }

    for (auto v : bad) {
        ans[v] = S[0];
        S.pop_front();
    }

    // GETTING ANS PROCESS END

    // ANS FIND BEGIN

    int ANS = 0;

    function<void(int)> GO = [&](int u) {
        vis[u] = 1;
        for (auto v : G[u]) {
            ANS += abs(ans[u] - ans[v]);
            if (vis[v] == -1) {
                GO(v);
            }
        }
    };

    for (int i = 0; i < n; i++) {
        vis[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        if (vis[i] == -1) {
            GO(i);
        }
    }

    // ANS FIND END

    cout << ANS << '\n';
}

signed main() {
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
